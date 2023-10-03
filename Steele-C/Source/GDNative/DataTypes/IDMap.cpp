#include "IDMap.h"
#include "GDNative/Common.h"


void godot::IDMap::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("has_id", "id"), &IDMap::has_id);
	ClassDB::bind_method(D_METHOD("has_name", "name"), &IDMap::has_name);
	ClassDB::bind_method(D_METHOD("get_id", "name"), &IDMap::get_id);
	ClassDB::bind_method(D_METHOD("get_name", "id"), &IDMap::get_name);
	ClassDB::bind_method(D_METHOD("add", "name"), &IDMap::add);
	ClassDB::bind_method(D_METHOD("update", "id", "new_name"), &IDMap::update);
	ClassDB::bind_method(D_METHOD("remove_by_id", "id"), &IDMap::remove_by_id);
	ClassDB::bind_method(D_METHOD("remove_by_name", "name"), &IDMap::remove_by_name);
}


bool godot::IDMap::has_id(int id) const
{
	return m_map.has(id);
}

bool godot::IDMap::has_name(const godot::String& s) const
{
	return m_map.has(to_str(s));
}

int godot::IDMap::get_id(const godot::String& s) const
{
	return m_map.get(to_str(s));
}

godot::String godot::IDMap::get_name(int id) const
{
	return to_str(m_map.get(id));
}

int godot::IDMap::add(const godot::String& name)
{
	return m_map.add(to_str(name));
}

bool godot::IDMap::update(int id, const godot::String& newName)
{
	return m_map.update(id,to_str(newName));
}

bool godot::IDMap::remove_by_id(int id)
{
	return m_map.remove(id);
}

bool godot::IDMap::remove_by_name(const godot::String& name)
{
	auto id = m_map.get(to_str(name));
	
	if (id == NULL_ID)
		return false;
	
	return m_map.remove(id);
}