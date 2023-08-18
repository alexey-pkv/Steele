#include "Direction.h"


using namespace Steele;


const Direction Direction::North(DirectionValue::North);  
const Direction Direction::NorthEast(DirectionValue::NorthEast);
const Direction Direction::East(DirectionValue::East);
const Direction Direction::SouthEast(DirectionValue::SouthEast);
const Direction Direction::South(DirectionValue::South);
const Direction Direction::SouthWest(DirectionValue::SouthWest);
const Direction Direction::West(DirectionValue::West);
const Direction Direction::NorthWest(DirectionValue::NorthWest);


const char* Direction::m_directionStrings[8] = {
	"North",
	"NorthEast",
	"East",
	"SouthEast",
	"South",
	"SouthWest",
	"West",
	"NorthWest"
};

godot::Vector2 Direction::Rotate(const godot::Vector2& source) const 
{
	if (m_direction == DirectionValue::North)
		return source;
	
	if (m_direction == DirectionValue::South) 
		return { -source.x, -source.y };
	
	if (m_direction == DirectionValue::East) 
		return { source.y, -source.x };
	
	if (m_direction == DirectionValue::West) 
		return { -source.y, source.x };
	
	return {};
}

godot::Vector2i Direction::Rotate(const godot::Vector2i& source) const
{
	if (m_direction == DirectionValue::North)
		return source;
	
	if (m_direction == DirectionValue::South) 
		return -1 * source;
	
	if (m_direction == DirectionValue::East) 
		return { source.y, -source.x };
	
	if (m_direction == DirectionValue::West) 
		return { -source.y, source.x };
	
	return {};
}

godot::Vector3 Direction::Rotate(const godot::Vector3& source) const
{
	if (m_direction == DirectionValue::North)
		return source;
	
	if (m_direction == DirectionValue::South) 
		return { -source.x, -source.y, source.z };
	
	if (m_direction == DirectionValue::East) 
		return { source.y, -source.x, source.z };
	
	if (m_direction == DirectionValue::West) 
		return { -source.y, source.x, source.z };
	
	return {};
}

godot::Vector3i Direction::Rotate(const godot::Vector3i& source) const
{
	if (m_direction == DirectionValue::North)
		return source;
	
	if (m_direction == DirectionValue::South) 
		return { -source.x, -source.y, source.z };
	
	if (m_direction == DirectionValue::East) 
		return { source.y, -source.x, source.z };
	
	if (m_direction == DirectionValue::West) 
		return { -source.y, source.x, source.z };
	
	return {};
}

void Direction::RotateInPlace(godot::Vector2 &source) const 
{
	if (m_direction == DirectionValue::North) return;
	
	if (m_direction == DirectionValue::South) 
		source *= -1;
	else if (m_direction == DirectionValue::East) 
		source = { source.y, -source.x };
	else if (m_direction == DirectionValue::West) 
		source = { -source.y, source.x };
}

void Direction::RotateInPlace(godot::Vector2i& source) const
{
	if (m_direction == DirectionValue::North) return;
	
	if (m_direction == DirectionValue::South) 
		source *= -1;
	else if (m_direction == DirectionValue::East) 
		source = { source.y, -source.x };
	else if (m_direction == DirectionValue::West) 
		source = { -source.y, source.x };
}

void Direction::RotateInPlace(godot::Vector3& source) const
{
	if (m_direction == DirectionValue::North) return;
	
	if (m_direction == DirectionValue::South) 
		source = { -source.x, -source.y, source.z };
	else if (m_direction == DirectionValue::East) 
		source = { source.y, -source.x, source.z };
	else if (m_direction == DirectionValue::West) 
		source = { -source.y, source.x, source.z };
}

void Direction::RotateInPlace(godot::Vector3i& source) const
{
	if (m_direction == DirectionValue::North) return;
	
	if (m_direction == DirectionValue::South) 
		source = { -source.x, -source.y, source.z };
	else if (m_direction == DirectionValue::East) 
		source = { source.y, -source.x, source.z };
	else if (m_direction == DirectionValue::West) 
		source = { -source.y, source.x, source.z };
}