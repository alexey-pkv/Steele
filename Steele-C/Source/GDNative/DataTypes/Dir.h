#ifndef GODOT_DIR_H
#define GODOT_DIR_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Direction.h"


namespace godot
{
	class Dir: public Object
	{
		GDCLASS(Dir, Object) // NOLINT(*-use-auto)
		
		
	private:
		Dir();
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		static int get(int dir);
		static int add(int a, int b);
		static int sub(int a, int b);
		static int mul(int a, int by);
		static Vector2i mul_v2i(int a, Vector2i v);
		static Vector3i mul_v3i(int a, Vector3i v);
		static Vector2 mul_v2(int a, Vector2 v);
		static Vector3 mul_v3(int a, Vector3 v);
		
		
	public:
		enum Direction
		{
			NORTH		= 0b0000,
			NORTH_EAST	= 0b0001,
			EAST		= 0b0010,
			SOUTH_EAST	= 0b0011,
			SOUTH		= 0b0100,
			SOUTH_WEST	= 0b0101,
			WEST		= 0b0110,
			NORTH_WEST	= 0b0111
		};
	};
}


VARIANT_ENUM_CAST(Dir::Direction);


#endif