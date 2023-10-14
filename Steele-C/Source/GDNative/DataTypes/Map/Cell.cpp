#include "Cell.h"
using namespace godot;

void Cell::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_ground"), &Cell::get_ground);
	ClassDB::bind_method(D_METHOD("add_ground_tile", "tile"), &Cell::add_ground_tile);
	ClassDB::bind_method(D_METHOD("remove_ground_tile", "tile"), &Cell::remove_ground_tile);
	ClassDB::bind_method(D_METHOD("clear"), &Cell::clear);
}


Ref<Ground> Cell::get_ground() const
{
	Ref<Ground> c;

	c.instantiate();

	c->set_ground_c(m_cell.Ground);

	return c;
}


void Cell::add_ground_tile(const Ref<GroundTile>& tile)
{
	m_cell.add_ground_tile(tile->get_tile_c());
}

bool Cell::remove_ground_tile(const Ref<GroundTile>& tile)
{
	return m_cell.remove_ground_tile(tile->get_tile_c());
}

void Cell::clear()
{
	m_cell.clear();
}
