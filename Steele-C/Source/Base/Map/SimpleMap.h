#ifndef STEELE_SIMPLEMAP_H
#define STEELE_SIMPLEMAP_H


#include <map>

#include "IMap.h"
#include "Utils.h"


namespace Steele
{
	template <typename CELL>
	class SimpleMap : public IMap<CELL>
	{
	private:
		std::map<v3i, CELL> m_map;
		
	
	protected:
		void _set(const CELL &c, v3i at) override
		{
			m_map[at] = c;
		}
		
		void _set(CELL &&c, v3i at) override
		{
			m_map[at] = std::move(c);
		}
		
		
		CELL* _try_get(v3i at) override
		{
			auto kvp = m_map.find(at);
			
			if (kvp == m_map.end())
			{
				return nullptr;
			}
			
			return &kvp->second;
		}
		
		const CELL* _try_get(v3i at) const override
		{
			auto kvp = m_map.find(at);
			
			if (kvp == m_map.end())
			{
				return nullptr;
			}
			
			return &kvp->second;
		}
		
		CELL* _get(v3i at) override
		{
			auto kvp = m_map.find(at);
			
			if (kvp == m_map.end())
			{
				m_map.emplace(at, CELL());
			}
			else
			{
				return &kvp->second;
			}
			
			return &m_map[at];
		}
		
		bool _is_empty(v3i at) const override
		{
			return !contains(m_map, at);
		}
		
		bool _remove(v3i at) override
		{
			return remove(m_map, at);
		}
	
	public:
		void clear() override
		{
			m_map.clear();	
		}
	
	
	public:
		SimpleMap() = default;
		~SimpleMap() = default;
		
		
	public:
		typename std::map<v3i, CELL>::iterator begin() { return m_map.begin(); }
		typename std::map<v3i, CELL>::iterator end() { return m_map.end(); }
		typename std::map<v3i, CELL>::const_iterator begin() const { return m_map.begin(); }
		typename std::map<v3i, CELL>::const_iterator end() const { return m_map.end(); }
		
	};
}


#endif