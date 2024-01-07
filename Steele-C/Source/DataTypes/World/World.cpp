#include "World.h"


using namespace Steele;


Map* World::get_map(const std::string& name)
{
	auto v = m_maps.find(name);
	
	if (v != m_maps.end())
	{
		return nullptr;
	}
	
	return v->second.get();
}


void World::set_active_actor(t_id id)
{
	m_activeActors.insert(id);
}

void World::set_inactive_actor(t_id id)
{
	m_activeActors.erase(id);
}

bool World::is_actor_active(t_id id)
{
	return contains(m_activeActors, id);
}
