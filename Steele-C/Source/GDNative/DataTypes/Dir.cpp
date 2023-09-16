#include "Dir.h"


void godot::Dir::_bind_methods()
{
	// Methods
	ClassDB::bind_static_method("Dir", D_METHOD("get", "dir"), &Dir::get);
	ClassDB::bind_static_method("Dir", D_METHOD("add", "a", "b"), &Dir::add);
	ClassDB::bind_static_method("Dir", D_METHOD("sub", "a", "b"), &Dir::sub);
	ClassDB::bind_static_method("Dir", D_METHOD("mul", "dir", "by"), &Dir::mul);
	ClassDB::bind_static_method("Dir", D_METHOD("mul_v2i", "dir", "vector"), &Dir::mul_v2i);
	ClassDB::bind_static_method("Dir", D_METHOD("mul_v3i", "dir", "vector"), &Dir::mul_v3i);
	ClassDB::bind_static_method("Dir", D_METHOD("mul_v2", "dir", "vector"), &Dir::mul_v2);
	ClassDB::bind_static_method("Dir", D_METHOD("mul_v3", "dir", "vector"), &Dir::mul_v3);
	
	// Consts
	BIND_CONSTANT(NORTH)
	BIND_CONSTANT(NORTH_EAST)
	BIND_CONSTANT(EAST)
	BIND_CONSTANT(SOUTH_EAST)
	BIND_CONSTANT(SOUTH)
	BIND_CONSTANT(SOUTH_WEST)
	BIND_CONSTANT(WEST)
	BIND_CONSTANT(NORTH_WEST)
}


godot::Dir::Dir()
{
	
}


int godot::Dir::get(int dir)
{
	return (int)(Steele::Direction(dir));
}

int godot::Dir::add(int a, int b)
{
	return (int)(Steele::Direction(a) + Steele::Direction(b));
}

int godot::Dir::sub(int a, int b)
{
	return (int)(Direction(a) - Direction(b));
}

int godot::Dir::mul(int a, int by)
{
	return (int)(Direction(a) * by);
}

godot::Vector2i godot::Dir::mul_v2i(int a, godot::Vector2i v)
{
	return v * Direction(a);
}

godot::Vector3i godot::Dir::mul_v3i(int a, godot::Vector3i v)
{
	return v * Direction(a);
}

godot::Vector2 godot::Dir::mul_v2(int a, godot::Vector2 v)
{
	return v * Direction(a);
}

godot::Vector3 godot::Dir::mul_v3(int a, godot::Vector3 v)
{
	return v * Direction(a);
}
