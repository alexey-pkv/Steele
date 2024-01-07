#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#ifndef GODOT_GENERATOR_H
#define GODOT_GENERATOR_H


#include <godot.hpp>
#include <godot_cpp/classes/node.hpp>

#include "Generation/GenerationScope.h"
#include "GDNative/Generation/Brushes/FillBrush.h"
#include "GDNative/RNG/RandomState.h"
#include "GDNative/DataTypes/Map/MapPatch.h"
#include "GDNative/DataTypes/ResourcesDBNode.h"


namespace godot
{
	class Generator : public Node
	{
		GDCLASS(Generator, Node)
	private:
		Steele::GenerationScope		m_scope;
		Ref<MapPatch>				m_map;
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		void abort();
		double get_progress();
		
		
	public:
		void set_rng_state(const Ref<RandomState>& state);
		void using_map_patch(const Ref<MapPatch>& map);
		void using_db(const ResourcesDBNode* db);
		
		
	public:
		bool generate_brush(t_id id, const Ref<Area>& area);
		bool generate_fill_brush(const Ref<FillBrush>& brush, const Ref<Area>& area);
	};
}


#endif

#pragma clang diagnostic pop