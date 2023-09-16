#include "Ground.h"


void godot::Ground::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("size"), &Ground::size);
	ClassDB::bind_method(D_METHOD("is_empty"), &Ground::is_empty);
	ClassDB::bind_method(D_METHOD("clear"), &Ground::clear);
	ClassDB::bind_method(D_METHOD("tiles"), &Ground::tiles);
	
	ClassDB::bind_method(D_METHOD("has", "id"), &Ground::has);
	ClassDB::bind_method(D_METHOD("remove", "id"), &Ground::remove);
	
	ClassDB::bind_method(D_METHOD("set_tile", "tile"), &Ground::set_tile);
	ClassDB::bind_method(D_METHOD("has_tile", "tile"), &Ground::has_tile);
	ClassDB::bind_method(D_METHOD("add_tile", "tile"), &Ground::add_tile);
	
	ClassDB::bind_method(D_METHOD("add", "id", "direction", "index"), &Ground::add);
	ClassDB::bind_method(D_METHOD("set", "id", "direction", "index"), &Ground::set);
}


godot::Ground::Ground(const Steele::Ground& ground) : 
	m_ground()
{
	
}

godot::Ground::Ground(Steele::Ground&& ground) : 
	m_ground(std::move(ground))
{
	
}


int godot::Ground::size() const
{
	return (int)m_ground.size();
}

bool godot::Ground::is_empty() const
{
	return m_ground.is_empty();
}

void godot::Ground::clear()
{
	m_ground.clear();
}

void godot::Ground::add_tile(const godot::Ref<godot::GroundTile>& tile)
{
	m_ground.add(tile->tile());
}

void godot::Ground::add(int id, int direction, int index)
{
	m_ground.add(id, Steele::Direction(direction), index);
}

void godot::Ground::set_tile(const godot::Ref<godot::GroundTile>& tile)
{
	m_ground.set(tile->tile());
}

void godot::Ground::set(int id, int direction, int index)
{
	m_ground.set(id, Steele::Direction(direction), index);
}

bool godot::Ground::remove(int id)
{
	return m_ground.remove(id);
}

bool godot::Ground::has(int id) const
{
	return m_ground.has(id);
}

bool godot::Ground::has_tile(const godot::Ref<godot::GroundTile>& tile) const
{
	return m_ground.has(tile->tile());
}


godot::Array godot::Ground::tiles() const
{
	auto a = godot::Array();
	
	for (const auto& c : m_ground)
	{
		godot::Ref<godot::GroundTile> g;
		
		g.instantiate();
		*(g.ptr()) = c;
		
		a.append(g);
	}
	
	return a;
}
