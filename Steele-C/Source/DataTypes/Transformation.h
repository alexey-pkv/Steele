#ifndef STEELE_TRANSFORMATION_H
#define STEELE_TRANSFORMATION_H


#include "../DataTypes/Direction.h"
#include "godot_cpp/variant/vector3i.hpp"

namespace Steele
{
	struct Transformation
	{
	public:
		Direction		Dir		= Direction::North;
		godot::Vector3i	Offset	= { 0, 0, 0 };
	
		
	public:
		inline void Add(Direction dir, godot::Vector3i offset) { Dir += dir; Offset += offset; }
		inline void Sub(Direction dir, godot::Vector3i offset) { Dir -= dir; Offset -= offset; }
		
		inline void operator+=(const Transformation& t) { Dir += t.Dir; Offset += t.Offset; }
		inline void operator-=(const Transformation& t) { Dir -= t.Dir; Offset -= t.Offset; }
		
		inline void operator+=(const godot::Vector3i& offset) { Offset += offset; }
		inline void operator-=(const godot::Vector3i& offset) { Offset -= offset; }
		
		inline void operator+=(Direction dir) { Dir += dir; }
		inline void operator-=(Direction dir) { Dir -= dir; }
		
		
		inline Transformation operator+(const Transformation& t) { return { .Dir = Dir + t.Dir, .Offset = Offset += t.Offset }; }
		inline Transformation operator-(const Transformation& t) { return { .Dir = Dir - t.Dir, .Offset = Offset -= t.Offset }; }
		
		inline Transformation operator+(const godot::Vector3i& offset) { return { .Dir = Dir, .Offset = Offset + offset }; }
		inline Transformation operator-(const godot::Vector3i& offset) { return { .Dir = Dir, .Offset = Offset - offset }; }
		
		inline Transformation operator+(Direction dir) { return { .Dir = Dir + dir, .Offset = Offset }; }
		inline Transformation operator-(Direction dir) { return { .Dir = Dir - dir, .Offset = Offset }; }
		
		
	public:
		godot::Vector3i Apply(godot::Vector3i target);
	};
	
	
	inline static godot::Vector3i operator*(const godot::Vector3i& v, const Transformation& t) 
	{
		return v * t.Dir + t.Offset;
	}
}


#endif