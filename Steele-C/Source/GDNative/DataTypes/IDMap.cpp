#include "IDMap.h"
#include "GDNative/Common.h"


void godot::IDMap::_bind_methods()
{
	ClassDB::bind_static_method("IDMap",D_METHOD("has_id", "id"),				&IDMap::has_id);
	ClassDB::bind_static_method("IDMap",D_METHOD("has_name", "name"),			&IDMap::has_name);
	ClassDB::bind_static_method("IDMap",D_METHOD("get_id", "name"),				&IDMap::get_id);
	ClassDB::bind_static_method("IDMap",D_METHOD("get_name", "id"),				&IDMap::get_name);
	ClassDB::bind_static_method("IDMap",D_METHOD("add", "name"),				&IDMap::add);
	ClassDB::bind_static_method("IDMap",D_METHOD("update", "id", "new_name"),	&IDMap::update);
	ClassDB::bind_static_method("IDMap",D_METHOD("remove_by_id", "id"),			&IDMap::remove_by_id);
	ClassDB::bind_static_method("IDMap",D_METHOD("remove_by_name", "name"),		&IDMap::remove_by_name);
}


bool godot::IDMap::has_id(int id)
{
	return map().has(id);
}

bool godot::IDMap::has_name(const godot::String& s)
{
	return map().has(to_std_str(s));
}

int godot::IDMap::get_id(const godot::String& s)
{
	return map().get(to_std_str(s));
}

godot::String godot::IDMap::get_name(int id)
{
	return to_godot_str(map().get(id));
}

int godot::IDMap::add(const godot::String& name)
{
	return map().add(to_std_str(name));
}

bool godot::IDMap::update(int id, const godot::String& newName)
{
	return map().update(id, to_std_str(newName));
}

bool godot::IDMap::remove_by_id(int id)
{
	return map().remove(id);
}

bool godot::IDMap::remove_by_name(const godot::String& name)
{
	auto id = map().get(to_std_str(name));
	
	if (id == STEELE_NULL_ID)
		return false;
	
	return map().remove(id);
}