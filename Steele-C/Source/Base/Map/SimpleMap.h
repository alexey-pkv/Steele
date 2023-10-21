#ifndef STEELE_SIMPLEMAP_H
#define STEELE_SIMPLEMAP_H


#include <map>

#include "IMap.h"
#include "Utils.h"
#include "DataTypes/Area.h"
#include "Exceptions/SteeleException.h"


namespace Steele
{
	template <typename CELL>
	class SimpleMap : public IMap<CELL>
	{
	public:
		static const auto MAX_MAP_SIZE_TO_CALCULATE_AREA = 1000 * 1000;
		
		
	private:
		std::map<v3i, CELL> m_map;
		
		mutable Area m_area = Area::ZERO;
		mutable bool m_areaCalculated = false;
		
		
	private:
		inline void clear_area()
		{
			if (m_areaCalculated)
			{
				m_areaCalculated = false;
				m_area.clear();
			}
		}
		
		
	public:
		bool is_debug = false;
		
	
	protected:
		void _set(const CELL &c, v3i at) override
		{
			if (is_debug)
				cout << "Set " << at.x << ":" << at.y << endl;
			
			if (m_areaCalculated && contains(m_map, at))
				clear_area();
			
			m_map[at] = c;
		}
		
		void _set(CELL &&c, v3i at) override
		{
			if (is_debug)
				cout << "Set " << at.x << ":" << at.y << endl;
			
			if (m_areaCalculated && contains(m_map, at))
				clear_area();
			
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
				clear_area();
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
			if (remove(m_map, at))
			{
				clear_area();
				return true;
			}
			
			return false;
		}
	
	public:
		void clear() override
		{
			clear_area();
			m_map.clear();	
		}
		
		Area get_area() const
		{
			if (m_areaCalculated)
				return m_area;
			
			if (m_map.size() > MAX_MAP_SIZE_TO_CALCULATE_AREA)
				throw Steele::SteeleException("Map size to big to calculate area!");
			
			m_area.clear();
			
			for (const auto &[pos, _] : m_map)
			{
				m_area += v2i { pos.x, pos.y };
			}
			
			m_areaCalculated = true;
			
			return m_area;
		}
	
	
	public:
		SimpleMap() = default;
		SimpleMap(const SimpleMap&) = default;
		SimpleMap(SimpleMap&&) = default;
		~SimpleMap() = default;
		
		
	public:
		inline size_t size() const { return m_map.size(); }
		
		typename std::map<v3i, CELL>::iterator begin() { return m_map.begin(); }
		typename std::map<v3i, CELL>::iterator end() { return m_map.end(); }
		typename std::map<v3i, CELL>::const_iterator begin() const { return m_map.begin(); }
		typename std::map<v3i, CELL>::const_iterator end() const { return m_map.end(); }
		
		
	public: // JSON
		template<class ... ARG>
		void json_write(nlohmann::json& into, const ARG& ... args) const
		{
			if (m_map.empty())
			{
				into = nlohmann::json::value_t::null; 
				return;
			}
			
			into = nlohmann::json::array();
			
			for (auto& it : m_map)
			{
				nlohmann::json item = {
					{ "at",		Steele::json_write(it.first) },
					{ "cell",	nlohmann::json() }
				};
				
				into.emplace_back(item);
				
				it.second.json_write(into.back()["cell"], args ... );
			}
		}
		
		template<class ... ARG>
		void json_read(const nlohmann::json& from, const ARG& ... args)
		{
			clear();
			
			if (from.is_null())
				return;
			else if (!from.is_array())
				throw SteeleException("Map must be array");
			
			for (auto& item : from)
			{
				if (!item.is_object() || !item.contains("at") || !item.contains("cell"))
					throw SteeleException("Invalid json format");
				
				v3i at = json_read_v3i(item["at"]);
				auto c = this->get(at);
				
				c->json_read(item["cell"], args ... );
			}
		}
	};
}


#endif