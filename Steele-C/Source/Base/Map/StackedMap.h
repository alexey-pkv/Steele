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
			
			explicit StackedCell(const CELL* cell) : IsEmpty(cell == nullptr) 
			{
				if (!IsEmpty)
				{
					Cell = *cell;
				}
			}
			
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
		std::vector<MapLayer> m_stack = std::vector<MapLayer>();
		MapLayer* m_top = nullptr;
		SimpleMap<CELL*> m_total = {};
		
		
	private:
		inline IMap<CELL>& get_map() { return this->next(); }
		inline const IMap<CELL>& get_map() const { return this->next(); }
		
		void pop_stack()
		{
			if (m_stack.empty())
				throw NotInTransactionException();
			
			m_top->clear();
			
			if (m_stack.size() == 1)
			{
				m_stack.clear();
			}
			else
			{
				m_stack.pop_back();
				m_top = &m_stack.back();
			}
		}
		
		
	public:
		explicit StackedMap(IMap<CELL>& map) : MapDecorator<CELL>(map) { m_stack.reserve(32); }
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
					StackedCell* cell = nullptr;
					
					typename std::vector<MapLayer>::iterator last = (m_stack.end() - 2);
					typename std::vector<MapLayer>::iterator first = m_stack.begin();
					
					for (auto map = last; map >= first && !cell; map--)
					{
						cell = map->try_get(at);
						
						if (map->try_get(at, &cell))
						{
							m_total.set(&(cell->Cell), at);
						}
					}
					
					if (!cell)
					{
						m_total.remove(at);
					}
				}
				
				pop_stack();
			}
		}
		
		void commit() override
		{
			if (m_stack.empty())
				throw NotInTransactionException();
			
			if (m_stack.size() == 1)
			{
				auto& map = get_map();
				
				for (auto & kvp : m_total)
				{
					auto at = kvp.first;
					CELL* cell = kvp.second;
					
					map.set(std::move(*cell), at);
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
				
				pop_stack();
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
		
		
	private:
		inline void set_top_cell(const CELL* c, v3i at) { set_top_cell(StackedCell(*c), at); }
		inline void set_top_cell(const CELL& c, v3i at) { set_top_cell(StackedCell(c), at); }
		inline void set_top_cell(CELL&& c, v3i at) { set_top_cell(StackedCell(std::move(c)), at); }
		
		void set_top_cell(const StackedCell& c, v3i at)
		{
			m_top->set(c, at);
			
			if (c.IsEmpty)
			{
				m_total.set(nullptr, at);
			}
			else
			{
				auto stacked = m_top->get(at);
				auto cell_addr = &stacked->Cell;
				
				m_total.set(cell_addr, at);
			}
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
				set_top_cell(StackedCell(c), at);
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
				set_top_cell(StackedCell(std::move(c)), at);
			}
		}
		
		CELL* _try_get(v3i at) override
		{
			if (!is_in_checkpoint())
				return get_map().try_get(at);
			
			auto stacked_c = m_top->try_get(at);
			
			if (stacked_c != nullptr)
			{
				return stacked_c->IsEmpty ? nullptr : &stacked_c->Cell;
			}
			
			auto previous = m_total.try_get(at);
			
			if (previous == nullptr)
			{
				auto primary = get_map().try_get(at);
			
				if (primary == nullptr)
				{
					return nullptr;
				}
				
				set_top_cell(primary, at);
			}
			else
			{
				set_top_cell(*previous, at);
			}
			
			return *m_total.get(at);
		}
		
		const CELL* _try_get(v3i at) const override
		{
			if (!is_in_checkpoint())
				return get_map().try_get(at);
			
			auto c = m_total.try_get(at);
			
			if (c != nullptr)
			{
				return *c;
			}
			
			return get_map().try_get(at);
		}
		
		CELL* _get(v3i at) override
		{
			if (!is_in_checkpoint())
				return get_map().get(at);
			
			// Get the cell from the top stack
			auto top_cell = m_top->try_get(at);
			
			if (top_cell != nullptr)
			{
				if (top_cell->IsEmpty)
				{
					set_top_cell(StackedCell(), at);
				}
				else
				{
					return &top_cell->Cell;
				}
			}
			else
			{
				auto cell = m_total.try_get(at);
				
				if (cell == nullptr)
				{
					set_top_cell(get_map().get(at), at);
				}
				else
				{
					set_top_cell(StackedCell(*cell), at);
				}
			}
			
			return *m_total.get(at);
		}
		
		bool _is_empty(v3i at) const override
		{
			if (is_in_checkpoint())
			{
				auto cell = m_total.try_get(at);
				
				if (cell != nullptr)
				{
					return *cell == nullptr;
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
			
			CELL** stacked_cell = m_total.try_get(at);
			
			// If a cell already exists in the stack, reset it to empty.
			if (stacked_cell)
			{
				if (*stacked_cell == nullptr)
				{
					return false;
				}
				
				*stacked_cell = nullptr;
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
				m_total.set(nullptr, at);
			}
			
			return true;
		}
	};
}


#endif