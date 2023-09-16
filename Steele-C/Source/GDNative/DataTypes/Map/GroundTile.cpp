#include "GroundTile.h"


void godot::GroundTile::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_index"), &GroundTile::get_index);
	ClassDB::bind_method(D_METHOD("set_index", "index"), &GroundTile::set_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "index"), "set_index", "get_index");
	
	ClassDB::bind_method(D_METHOD("get_tile"), &GroundTile::get_tile);
	ClassDB::bind_method(D_METHOD("set_tile", "tile"), &GroundTile::set_tile);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "tile"), "set_tile", "get_tile");
	
	ClassDB::bind_method(D_METHOD("get_direction"), &GroundTile::get_direction);
	ClassDB::bind_method(D_METHOD("set_direction", "direction"), &GroundTile::set_direction);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "direction"), "set_direction", "get_direction");
}

godot::GroundTile::GroundTile(Steele::GroundTile tile) : 
	m_tile(tile)
{
	
}


int godot::GroundTile::get_index() const { return m_tile.Index; }
int godot::GroundTile::get_tile() const { return m_tile.ID; }
int godot::GroundTile::get_direction() const { return (int)m_tile.Dir; }
void godot::GroundTile::set_index(int index) { m_tile.Index = index; }
void godot::GroundTile::set_tile(int tile) { m_tile.ID = tile; }
void godot::GroundTile::set_direction(int direction) { m_tile.Dir = Steele::Direction(direction); }

