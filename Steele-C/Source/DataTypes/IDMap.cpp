#include "IDMap.h"


#include "Exceptions/SteeleException.h"


using namespace std;
using namespace Steele;


IDMap IDMap::m_global = {};


t_id IDMap::add(const string& name)
{
	if (has(name))
		return STEELE_NULL_ID;
	
	auto id = m_nextID++;
	
	m_byName[name] = id;
	m_byID[id] = name;
	
	return id;
}

bool IDMap::update(t_id id, const std::string& newName)
{
	auto currentID = get(newName);
	
	if (currentID == id)
		return true;
	if (currentID != STEELE_NULL_ID)
		return false;
	
	auto currentName = get(id);
	
	::remove(m_byName, currentName);
	
	m_byName[newName] = id;
	m_byID[id] = newName;
	
	return true;
}

bool IDMap::remove(t_id id)
{
	if (id == STEELE_NULL_ID || !has(id))
		return false;
	
	auto name = get(id);
	
	::remove(m_byName, name);
	::remove(m_byID, id);
	
	return true;
}

std::string IDMap::require(t_id id) const
{
	auto it = m_byID.find(id);
	
	if (it == m_byID.end())
	{
		
	}
	
	return it->second;
}

t_id IDMap::require(const std::string& name) const
{
	auto it = m_byName.find(name);
	
	if (it == m_byName.end())
	{
		
	}
	
	return it->second;
}


void IDMap::debug_clear()
{
	m_byName.clear();
	m_byID.clear();
}

void IDMap::debug_add(t_id id, const std::string& name)
{
	if (has(name) || has(id))
		throw Steele::SteeleException("Can directly debug_add id and name only if both do not exist");
	
	m_byName[name] = id;
	m_byID[id] = name;
	
	m_nextID = std::max(m_nextID, id + 1);
}