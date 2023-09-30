#ifndef GODOT_GROUND_H
#define GODOT_GROUND_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Map/Ground.h"
#include "GroundTile.h"


namespace godot
{
	class Ground : public RefCounted
	{
		GDCLASS(Ground, RefCounted) // NOLINT(*-use-auto)	
	private:
		Steele::Ground m_ground;
		
	public:
		~Ground() override = default;
		Ground() = default;
		
		Ground(const Steele::Ground& ground);
		Ground(Steele::Ground&& ground);
		
		
	public:
		inline Steele::Ground& ground() { return m_ground; }
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		int size() const;
		bool is_empty() const;
		void clear();
		
		
		void add_tile(const Ref<GroundTile>& tile);
		void add(int id, int direction, int index);
		void set_tile(const Ref<GroundTile>& tile);
		void set(int id, int direction, int index);
		bool remove(int id);
		bool has(int id) const;
		bool has_tile(const Ref<GroundTile>& tile) const;
		
		Array tiles() const;

	public:
		inline void set_ground_c(Steele::Ground ground) { m_ground = ground; };
	};
}


#endif