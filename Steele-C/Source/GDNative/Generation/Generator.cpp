#include "Generator.h"


void Generator::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("abort"),									&Generator::abort);
	ClassDB::bind_method(D_METHOD("get_progress"),							&Generator::get_progress);
	ClassDB::bind_method(D_METHOD("set_rng_state", "state"),				&Generator::set_rng_state);
	ClassDB::bind_method(D_METHOD("using_map_patch", "map"),				&Generator::using_map_patch);
	ClassDB::bind_method(D_METHOD("using_db", "db"),						&Generator::using_db);
	ClassDB::bind_method(D_METHOD("generate_fill_brush", "brush", "area"),	&Generator::generate_fill_brush);
}


void Generator::abort()				{ m_scope.abort(); }
double Generator::get_progress()	{ return m_scope.get_progress(); }


void Generator::set_rng_state(const Ref<RandomState>& state)
{
	m_scope.set_rng_state(state->get_steele_state());
}

void Generator::using_map_patch(const Ref<MapPatch>& map)
{
	if (map.is_null())
	{
		m_scope.using_map(nullptr);
	}
	else
	{
		m_scope.using_map(map->steele_map());
	}
}

void Generator::using_db(const ResourcesDBNode* db)
{
	m_scope.using_db(db->db());
}


bool Generator::generate_fill_brush(const Ref<FillBrush>& brush, const Ref<Area>& area)
{
	return m_scope.generate(brush->steele_brush(), area->steele_area());
}
