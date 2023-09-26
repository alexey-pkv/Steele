#include "Transformation.h"


godot::Vector3i Steele::Transformation::apply(godot::Vector3i target) const
{
	target = Dir.Rotate(target);
	target = target + Offset;
	
	return target;
}


const Steele::Transformation Steele::Transformation::ZERO	= {};