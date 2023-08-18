#include "Transformation.h"


godot::Vector3i Steele::Transformation::Apply(godot::Vector3i target)
{
	target = target - Offset;
	target = Dir.Rotate(target);
	
	return target;
}
