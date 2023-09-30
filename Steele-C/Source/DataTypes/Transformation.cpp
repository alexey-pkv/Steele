#include "Transformation.h"


Steele::Transformation::Transformation(v3i offset, Steele::Direction dir) : 
	Offset(offset),
	Dir(dir)
{
	
}

Steele::Transformation::Transformation(v3i offset) : 
	Offset(offset)
{
	
}

Steele::Transformation::Transformation(v2i offset, Steele::Direction dir) : 
	Offset(to_v3i(offset)),
	Dir(dir)
{
	
}

Steele::Transformation::Transformation(v2i offset) : 
	Offset(to_v3i(offset))
{
	
}

Steele::Transformation::Transformation(Steele::Direction dir) :
	Dir(dir)
{
	
}


godot::Vector3i Steele::Transformation::apply(godot::Vector3i target) const
{
	target = Dir.Rotate(target);
	target = target + Offset;
	
	return target;
}

void Steele::Transformation::apply_ref(godot::Vector3i& target) const
{
	Dir.RotateInPlace(target);
	target += Offset;
}


const Steele::Transformation Steele::Transformation::ZERO	= {};