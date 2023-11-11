#include "MapPatch.h"


void MapPatch::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("area"), &MapPatch::area);
	ClassDB::bind_method(D_METHOD("size"), &MapPatch::size);
	
	
	ClassDB::bind_method(D_METHOD("has", "x", "y", "z"), &MapPatch::has);
	ClassDB::bind_method(D_METHOD("has_v3i", "at"), &MapPatch::has_v3i);
	ClassDB::bind_method(D_METHOD("has_v2i", "at"), &MapPatch::has_v2i);
	
	ClassDB::bind_method(D_METHOD("get", "x", "y", "z"), &MapPatch::get);
	ClassDB::bind_method(D_METHOD("get_v3i", "at"), &MapPatch::get_v3i);
	ClassDB::bind_method(D_METHOD("get_v2i", "at"), &MapPatch::get_v2i);
	
	ClassDB::bind_method(D_METHOD("set", "x", "y", "z", "c"), &MapPatch::set);
	ClassDB::bind_method(D_METHOD("set_v3i", "at", "c"), &MapPatch::set_v3i);
	ClassDB::bind_method(D_METHOD("set_v2i", "at", "c"), &MapPatch::set_v2i);
	
	ClassDB::bind_method(D_METHOD("remove", "x", "y", "z"), &MapPatch::remove);
	ClassDB::bind_method(D_METHOD("remove_v3i", "at"), &MapPatch::remove_v3i);
	ClassDB::bind_method(D_METHOD("remove_v2i", "at"), &MapPatch::remove_v2i);
}


MapPatch::MapPatch(Steele::SimpleMap<Steele::Cell>& source) : 
	m_patch(source)
{
	
}


Ref<godot::Area> MapPatch::area() const
{
	Ref<Area> area;
	
	area.instantiate();
	area->steele_area() = m_patch.get_area();
	
	return area; 
}

int MapPatch::size() const
{
	return (int)m_patch.size();
}

bool MapPatch::has(int x, int y, int z) const
{
	return !m_patch.is_empty(x, y, z);
}

bool MapPatch::has_v3i(v3i at) const
{
	return !m_patch.is_empty(at);
}

bool MapPatch::has_v2i(v2i at) const
{
	return !m_patch.is_empty(at);
}

Ref<Cell> MapPatch::get(int x, int y, int z) const
{
	Ref<Cell> r_cell;
	get_c(x, y, z, r_cell);
	return r_cell;
}

Ref<Cell> MapPatch::get_v3i(v3i at) const
{
	Ref<Cell> r_cell;
	get_v3i_c(at, r_cell);
	return r_cell;
}

Ref<Cell> MapPatch::get_v2i(v2i at) const
{
	Ref<Cell> r_cell;
	get_v2i_c(at, r_cell);
	return r_cell;
}

void MapPatch::get_c(int x, int y, int z, Ref<Cell>& into) const
{
	get_v3i_c(v3i(x, y, z), into);
}

void MapPatch::get_v3i_c(v3i at, Ref<Cell>& into) const
{
	auto cell = m_patch.try_get(at);
	
	if (cell != nullptr)
	{
		if (into.is_null())
		{
			into.instantiate();
		}
		
		into->set(cell);
	}
	else
	{
		into.unref();
	}
}

void MapPatch::get_v2i_c(v2i at, Ref<Cell>& into) const
{
	get_v3i_c(to_v3i(at), into);
}

void MapPatch::set(int x, int y, int z, const Ref<Cell>& cell)
{
	m_patch.set(cell->steele_cell(), x, y, z);
}

void MapPatch::set_v3i(v3i at, const Ref<Cell>& cell)
{
	m_patch.set(cell->steele_cell(), at);
}

void MapPatch::set_v2i(v2i at, const Ref<Cell>& cell)
{
	m_patch.set(cell->steele_cell(), at);
}

bool MapPatch::remove(int x, int y, int z)
{
	return m_patch.remove(x, y, z);
}

bool MapPatch::remove_v3i(v3i at)
{
	return m_patch.remove(at);
}

bool MapPatch::remove_v2i(v2i at)
{
	return m_patch.remove(at);
}
