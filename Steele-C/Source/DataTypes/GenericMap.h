#ifndef STEELE_GENERICMAP_H
#define STEELE_GENERICMAP_H


#include <map>
#include <vector>

#include "Utils.h"
#include "Types.h"
#include "TransformationStack.h"


namespace Steele
{
	template <typename CELL>
	class AbstractGenericMap
	{
	protected:
		virtual const CELL* GetCell(const v3i& at) const = 0;
		virtual const CELL* GetOrCreateCell(const v3i& at) = 0;
		virtual void SetCell(const v3i& at, const CELL* cell) = 0;
		virtual bool IsCellEmpty(const v3i& at) const = 0;
		
	protected:
		virtual void PushTransformationStack(const Transformation& t) = 0;
		virtual bool PopTransformationStack() = 0;
		
		
	public:
		inline const CELL* Get(const v3i& at) const { return GetCell(at); }
		inline const CELL* Get(int x, int y) const { return GetCell({x, y, 0}); }
		inline const CELL* Get(int x, int y, int z) const { return GetCell({x, y, z}); }
		inline const CELL* Get(const v2i& at) const { return GetCell({at.x, at.y, 0}); }
		inline const CELL* Get(const v2i& at, int z) { return GetCell({at.x, at.y, z}); }
		inline const CELL* GetOrCreate(const v3i& at) { return GetOrCreateCell(at); }
		inline const CELL* GetOrCreate(int x, int y) { return GetOrCreateCell({x, y, 0}); }
		inline const CELL* GetOrCreate(int x, int y, int z) { return GetOrCreateCell({x, y, z}); }
		inline const CELL* GetOrCreate(const v2i& at) { return GetOrCreateCell({at.x, at.y, 0}); }
		inline const CELL* GetOrCreate(const v2i& at, int z) { return GetOrCreateCell({at.x, at.y, z}); }
		
		inline void Set(int x, int y, const CELL* cell) { SetCell({ x, y, 0 }, cell); };
		inline void Set(int x, int y, const CELL& cell) { SetCell({ x, y, 0 }, &cell); };
		inline void Set(int x, int y, int z, const CELL* cell) { SetCell({ x, y, z }, cell); };
		inline void Set(int x, int y, int z, const CELL& cell) { SetCell({ x, y, z }, &cell); };
		inline void Set(const v2i& at, const CELL* cell) { SetCell({ at.x, at.y, 0 }, cell); };
		inline void Set(const v2i& at, const CELL& cell) { SetCell({ at.x, at.y, 0 }, &cell); };
		inline void Set(const v2i& at, int z, const CELL* cell) { SetCell({ at.x, at.y, z }, cell); };
		inline void Set(const v2i& at, int z, const CELL& cell) { SetCell({ at.x, at.y, z }, &cell); };
		inline void Set(const v3i& at, const CELL* cell) { SetCell(at, cell); };
		inline void Set(const v3i& at, const CELL& cell) { SetCell(at, &cell); };
		inline bool IsEmpty(const v3i& at) const { return IsCellEmpty(at); }
		inline bool Remove(const v3i& at) { return SetCell(at, nullptr); }
		inline bool IsEmpty(int x, int y, int z) { return IsEmpty({x, y, z}); }
		inline bool IsEmpty(const v2i& at, int z) { return IsEmpty({at.x, at.y, z}); }
		inline bool Remove(int x, int y, int z) { return Remove({x, y, z}); }
		inline bool Remove(const v2i& at, int z) { return Remove({at.x, at.y, z}); }
		
	public:
		inline void PushTransformation(const v3i& t, Direction dir) { PushTransformationStack({ .Dir = dir, .Offset = t }); }
		inline void PushTransformation(const Transformation& t) { PushTransformationStack(t); }
		inline bool PopTransformation() { return PopTransformationStack(); }
		
	public:
		virtual void PushMapStack() = 0;
		virtual bool RollbackMap() = 0;
		virtual bool CommitMap() = 0;
		virtual void RollbackAllMaps() = 0;
		virtual void CommitAllMaps() = 0;
		virtual int GetMapStackSize() const = 0;
		
		inline bool IsStacked() const { return GetMapStackSize() > 0; }
	};
	
	template <typename CELL>
	class GenericMap : public AbstractGenericMap<CELL>
	{
	private:
		struct StuckCell
		{
			bool IsEmpty = false;
			CELL Cell;
		};
	private:
		std::map<v3i, CELL>						m_map;
		std::vector<std::map<v3i, StuckCell>>	m_mapsStack;
		std::map<v3i, StuckCell>*				m_topMap = nullptr;
		std::map<v3i, StuckCell>				m_stackMap;
		
		TransformationStack	m_transformation;
		
		
	private:
		void ClearMapStack()
		{
			m_topMap = nullptr;
			m_stackMap.clear();
			m_mapsStack.clear();
		}
		
		const CELL* CreateCell(const v3i& at)
		{
			auto v = at * m_transformation;
			
			if (this->IsStacked())
			{
				auto res = m_topMap->emplace(v, StuckCell { .IsEmpty = false, .Cell = {} });
				return &(res.first->second.Cell);
			}
			else
			{
				auto res = m_map.emplace(v, CELL {});
				return &(res.first->second);
			}
		}
		
		void PopMapStack()
		{
			m_mapsStack.pop_back();
			m_topMap = &m_mapsStack.back();
		}
		
		
	public:
		GenericMap() = default;
		~GenericMap() = default;
	
	
	protected:
		const CELL* GetCell(const v3i& at) const override
		{
			auto v = at * m_transformation;
			
			if (this->IsStacked())
			{
				auto stuckRes = m_stackMap.find(v);
				
				if (stuckRes != m_stackMap.end())
				{
					if (stuckRes->second.IsEmpty)
					{
						return nullptr;
					}
					else
					{
						return &(stuckRes->second.Cell);
					}
				}
			}
			
			auto res = m_map.find(v);
			
			return res == m_map.end() ? nullptr : &(res->second);
		}
		
		const CELL* GetOrCreateCell(const v3i& at) override
		{
			auto cell = GetCell(at);
			
			if (cell == nullptr)
			{
				CreateCell(at);
				cell = this->GetCell(at);
			}
			
			return cell;
		}
		
		void SetCell(const v3i& at, const CELL* cell) override
		{
			auto v = at * m_transformation;
			
			if (this->IsStacked())
			{
				auto curr = m_topMap->find(v);
				
				if (curr == m_topMap->end())
				{
					if (cell == nullptr)
					{
						m_topMap->emplace(v, StuckCell { .IsEmpty = true, .Cell = {} });
					}
					else
					{
						m_topMap->emplace(v, StuckCell { .IsEmpty = false, .Cell = *cell });
					}
				}
				else if (cell == nullptr)
				{
					curr->second.IsEmpty = true;
				}
				else
				{
					curr->second.Cell = *cell;
				}
			}
			else if (cell == nullptr)
			{
				remove(m_map, v);
			}
			else
			{
				m_map[v] = *cell;
			}
		}
		
		bool IsCellEmpty(const v3i& at) const override
		{
			auto v = at * m_transformation;
			
			if (this->IsStacked())
			{
				auto res = m_stackMap.find(v);
				
				if (res != m_stackMap.end())
				{
					return res->second.IsEmpty;
				}
			}
			
			return contains(m_map, v);
		}
		
		void PushTransformationStack(const Transformation& t) override
		{
			m_transformation.Push(t);
		}
		
		bool PopTransformationStack() override
		{
			return m_transformation.Pop();
		}
		
	public:
		void PushMapStack() override
		{
			m_mapsStack.push_back({});
			m_topMap = &m_mapsStack.back();
		}
		
		bool RollbackMap() override
		{
			if (m_stackMap.size() == 0)
				return false;
			
			if (m_stackMap.size() == 1)
			{
				RollbackAllMaps();
				return true;
			}
			
			for (auto kvp = m_topMap->begin(); kvp != m_topMap->end(); kvp++)
			{
				bool found = false;
				auto at = kvp->first;
				
				for (auto map = m_mapsStack.end() - 2; map >= m_mapsStack.begin(); map--)
				{
					auto res = map->find(at);
					
					if (res != map->end())
					{
						found = true;
						m_stackMap.emplace(at, res->second);
						break;
					}
				}
				
				if (!found)
				{
					remove(m_stackMap, at);
				}
			}
			
			PopMapStack();
			
			return true;
		}
		
		bool CommitMap() override
		{
			if (m_stackMap.size() == 0)
				return false;
			
			if (m_stackMap.size() == 1)
			{
				CommitAllMaps();
				return true;
			}
			
			std::map<v3i, StuckCell>* prev = &m_mapsStack[m_mapsStack.size() - 2];
			
			prev->insert(m_topMap->begin(), m_topMap->end());
			
			PopMapStack();
			
			return true;
		}
		
		int GetMapStackSize() const override
		{
			return (int)m_stackMap.size();
		}
		
		void RollbackAllMaps() override
		{
			ClearMapStack();
		}
		
		void CommitAllMaps() override
		{
			for (auto& kvp : m_stackMap)
			{
				if (kvp.second.IsEmpty)
				{
					remove(m_map, kvp.first);
				}
				else
				{
					m_map[kvp.first] = kvp.second.Cell;
				}
			}
			
			ClearMapStack();
		}
	};
}


#endif