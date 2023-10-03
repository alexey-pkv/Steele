#include "IDMap.h"


using namespace std;
using namespace Steele;


t_id IDMap::add(const string& name)
{
	if (has(name))
		return NULL_ID;
	
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
	if (currentID != NULL_ID)
		return false;
	
	auto currentName = get(id);
	
	::remove(m_byName, currentName);
	
	m_byName[newName] = id;
	m_byID[id] = newName;
	
	return true;
}

bool IDMap::remove(t_id id)
{
	if (id == NULL_ID || !has(id))
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
