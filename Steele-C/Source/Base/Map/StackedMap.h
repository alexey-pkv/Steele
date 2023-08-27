#ifndef STEELE_STACKEDMAP_H
#define STEELE_STACKEDMAP_H


#include "SimpleMap.h"
#include "MapDecorator.h"
#include "IStackableMap.h"

#include "Exceptions/MapExceptions.h"


namespace Steele
{
	template <typename CELL>
	class StackedMap : 
		public MapDecorator<CELL>,
		public IStackableMap
	{
	private:
		struct StackedCell
		{
			bool IsEmpty = true;
			CELL Cell;
			
		public:
			explicit StackedCell(const CELL& cell) : IsEmpty(false), Cell(cell) {}
			explicit StackedCell(CELL&& cell) : IsEmpty(false), Cell(std::move(cell)) {}
			
			StackedCell() = default;
			StackedCell(const StackedCell&) = default;
			StackedCell(StackedCell&&) = default;
			StackedCell& operator=(const StackedCell&) = default;
			StackedCell& operator=(StackedCell&&) = default;
			
			
		public:
			void apply(IMap<CELL>& map, v3i at)
			{
				if (IsEmpty)
				{
					map.remove(at);
				}
				else
				{
					map.set(std::move(Cell), at);
				}
			}
		};
		
		
		typedef SimpleMap<StackedCell> MapLayer;
		
		
	private:
		std::vector<MapLayer> m_stack = std::vector<MapLayer>(32);
		MapLayer* m_top = nullptr;
		MapLayer m_total = {};
		
		
	private:
		inline IMap<CELL>& get_map() { return this->next(); }
		inline const IMap<CELL>& get_map() const { return this->next(); }
		
		
	public:
		explicit StackedMap(IMap<CELL>& map) : MapDecorator<CELL>(map) {}
		~StackedMap() = default;
		
		
	public:
		void checkpoint() override
		{
			m_stack.push_back(MapLayer());
			m_top = &m_stack.back();
		}
		
		void rollback() override
		{
			if (m_stack.empty())
				throw NotInTransactionException();
			
			if (m_stack.size() == 1)
			{
				m_stack.clear();
				m_total.clear();
				m_top = nullptr;
			}
			else
			{
				for (auto kvp = m_top->begin(); kvp != m_top->end(); kvp++)
				{
					auto at = kvp->first;
					const StackedCell* cell = nullptr;
					
					typename std::vector<MapLayer>::iterator last = (m_stack.end() - 2);
					typename std::vector<MapLayer>::iterator first = m_stack.begin();
					
					for (auto map = last; map >= first && !cell; map--)
					{
						cell = map->try_get(at);
						
						if (map->try_get(at, &cell))
						{
							m_total.set(*cell, at);
						}
					}
					
					if (!cell)
					{
						m_total.remove(at);
					}
				}
			}
			
			m_stack.pop_back();
		}
		
		void commit() override
		{
			if (m_stack.empty())
				throw NotInTransactionException();
			
			if (m_stack.size() == 1)
			{
				auto& map = get_map();
				
				for (auto kvp = m_total.begin(); kvp != m_total.end(); kvp++)
				{
					auto at = kvp->first;
					StackedCell& cell = kvp->second;
					
					cell.apply(map, at);
				}
				
				m_stack.clear();
				m_top = nullptr;
			} 
			else
			{
				MapLayer& prev = m_stack[m_stack.size() - 2];
				
				for (auto kvp = m_top->begin(); kvp != m_top->end(); kvp++)
				{
					auto at = kvp->first;
					
					prev.set(std::move(kvp->second), at);
				}
				
				m_top->clear();
				m_top = &(*(m_stack.end() - 2));
				m_stack.pop_back();
			}
		}
		
		int stack_depth() const override
		{
			return m_stack.size();
		}
		
		bool is_in_checkpoint() const override
		{
			return !m_stack.empty();
		}
		
		
	public:
		void clear() override
		{
			m_stack.clear();
			m_total.clear();
			m_top = nullptr;
		}
	
	protected:
		void _set(const CELL &c, v3i at) override
		{
			if (!is_in_checkpoint())
			{
				get_map().set(c, at);
			}
			else
			{
				m_top->set(StackedCell(c), at);
				m_total.set(StackedCell(c), at);
			}
		}
		
		void _set(CELL&& c, v3i at) override
		{
			if (!is_in_checkpoint())
			{
				get_map().set(std::move(c), at);
			}
			else
			{
				auto stacked = StackedCell(std::move(c));
				
				m_total.set(stacked, at);
				m_top->set(std::move(stacked), at);
			}
		}
		
		CELL *_try_get(v3i at) override
		{
			if (is_in_checkpoint())
			{
				auto cell = m_total.try_get(at);
				
				if (cell != nullptr)
				{
					return (cell->IsEmpty ? nullptr : &cell->Cell);
				}
			}
			
			return get_map().try_get(at);
		}
		
		const CELL* _try_get(v3i at) const override
		{
			if (is_in_checkpoint())
			{
				auto cell = m_total.try_get(at);
				
				if (cell != nullptr)
				{
					return (cell->IsEmpty ? nullptr : &cell->Cell);
				}
			}
			
			return get_map().try_get(at);
		}
		
		CELL* _get(v3i at) override
		{
			if (is_in_checkpoint())
			{
				StackedCell* stacked_cell = m_total.try_get(at);
				
				if (!stacked_cell)
				{
					stacked_cell = m_top->get(at);
					m_total.set(*stacked_cell, at);
				}
				else
				{
					stacked_cell->IsEmpty = false;
					stacked_cell->Cell = {};
				}
				
				return &stacked_cell->Cell;
			}
			else
			{
				return get_map().get(at);
			}
		}
		
		bool _is_empty(v3i at) const override
		{
			if (is_in_checkpoint())
			{
				auto cell = m_total.try_get(at);
				
				if (cell != nullptr)
				{
					return cell->IsEmpty;
				}
			}
			
			return get_map().is_empty(at);
		}
		
		bool _remove(v3i at) override
		{
			if (!is_in_checkpoint())
			{
				return get_map().remove(at);
			}
			
			StackedCell* stacked_cell = m_total.try_get(at);
			
			// If a cell already exists in the stack, reset it to empty.
			if (stacked_cell)
			{
				if (stacked_cell->IsEmpty)
				{
					return false;
				}
				
				stacked_cell->IsEmpty = true;
				m_top->get(at)->IsEmpty = true;
			}
			// Otherwise, first check if the original map is empty.
			else if (get_map().is_empty(at))
			{
				return false;
			}
			// If not, create a new empty override cell. 
			else
			{
				m_top->set({}, at);
				m_total.set({}, at);
			}
			
			return true;
		}
	};
}


#endif