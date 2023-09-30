#ifndef STEELE_IDMAP_H
#define STEELE_IDMAP_H


#include <map>
#include <string>

#include "Types.h"
#include "Utils.h"


namespace Steele
{
	class IDMap
	{
	private:
		std::map<t_id, std::string>		m_byID;
		std::map<std::string, t_id>		m_byName;
		t_id							m_nextID	= 1;
		
		
	public:
		inline bool has(t_id id) { return contains(m_byID, id); }
		inline bool has(const std::string& s) { return contains(m_byName, s); }
		inline t_id get(const std::string& s) { return get_value(m_byName, s, NULL_ID); }
		inline std::string get(const t_id id) { return get_value(m_byID, id, std::string("")); }
		
		
	public:
		t_id add(const std::string& name);
		bool update(t_id id, const std::string& newName);
		bool remove(t_id id);
	};
}


#endif