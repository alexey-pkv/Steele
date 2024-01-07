#ifndef STEELE_WORLD_H
#define STEELE_WORLD_H


#include "Map.h"
#include "Utils.h"
#include "ChaosManager.h"


namespace Steele
{
	class World
	{
	private:
		ChaosManager						m_chaos;
		std::map<std::string, uptr<Map>>	m_maps;
		std::set<t_id>						m_activeActors;
		
		
	public:
		~World() = default;
		World() = default;
		
		
	public:
		World(const World&) = delete;
		World(World&&) = delete;
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;
		
		
	public:
		Map* get_map(const std::string& name);
		
		void set_active_actor(t_id id);
		void set_inactive_actor(t_id id);
		bool is_actor_active(t_id id);
	};
}


#endif