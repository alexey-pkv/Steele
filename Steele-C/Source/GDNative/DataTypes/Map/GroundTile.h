#ifndef GODOT_GROUNDTILE_H
#define GODOT_GROUNDTILE_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Map/Ground.h"


namespace godot
{
	class GroundTile : public RefCounted
	{
		GDCLASS(GroundTile, RefCounted) // NOLINT(*-use-auto)	
	private:
		Steele::GroundTile m_tile;
		
	public:
		~GroundTile() override = default;
		GroundTile() = default;
		GroundTile(Steele::GroundTile tile);
		
		
	public:
		inline Steele::GroundTile& tile() { return m_tile; }
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		int get_index() const;
		int get_tile() const;
		int get_direction() const;
		void set_index(int index);
		void set_tile(int tile);
		void set_direction(int direction);
	};
}


#endif