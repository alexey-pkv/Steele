#include "Transformation.h"


godot::Vector3i Steele::Transformation::apply(godot::Vector3i target) const
{
	target = target + Offset;
	target = Dir.Rotate(target);
	
	return target;
}


const Steele::Transformation Steele::Transformation::ZERO	= {};