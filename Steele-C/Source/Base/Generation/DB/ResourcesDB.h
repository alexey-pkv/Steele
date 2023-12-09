#ifndef STEELE_RESOURCESDB_H
#define STEELE_RESOURCESDB_H


#include <map>

#include "Utils.h"
#include "DataTypes/Types.h"
#include "Exceptions/SteeleException.h"


namespace Steele
{
	template<typename T>
	class ResourcesDB
	{
	private:
		std::map<t_id, T*>	m_db;
		
		
	protected:
		inline std::map<t_id, T*>&	db() { return m_db; };
		inline const std::map<t_id, const T*>& db() const { return m_db; };
		
		
	public:
		void set(t_id id, T* t)
		{
			m_db[id] = t;
		}
		
		bool has(t_id id) const
		{
			return contains(m_db, id);
		}
		
		T* get(t_id id)
		{
			auto kvp = m_db.find(id);
			return kvp == m_db.end() ? nullptr : kvp->second;
		}
		
		const T* get(t_id id) const
		{
			auto kvp = m_db.find(id);
			return kvp == m_db.end() ? nullptr : kvp->second;
		}
		
		T* require(t_id id)
		{
			auto res = get(id);
			
			if (!res)
				throw SteeleException("Object with id ", id, " not found");
			
			return res;
		}
		
		const T* require(t_id id) const
		{
			auto res = get(id);
			
			if (!res)
				throw SteeleException("Object with id ", id, " not found");
			
			return res;
		}
		
		bool remove(t_id id)
		{
			return ::remove(m_db, id);
		}
		
		void clear()
		{
			m_db.clear(); 
		}
		
		int count() const
		{
			return (int)(m_db.size()); 
		}
	};
}


#endif