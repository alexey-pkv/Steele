#ifndef STEELE_TRANSFORMATION_H
#define STEELE_TRANSFORMATION_H



#include "godot_cpp/variant/vector3i.hpp"
#include "DataTypes/Direction.h"


namespace Steele
{
	struct Transformation
	{
	public:
		Direction		Dir		= Direction::North;
		godot::Vector3i	Offset	= { 0, 0, 0 };
	
		
	public:
		inline void add(Direction dir, godot::Vector3i offset) { Dir += dir; Offset += offset; }
		inline void sub(Direction dir, godot::Vector3i offset) { Dir -= dir; Offset -= offset; }
		
		inline void operator+=(const Transformation& t) { Dir += t.Dir; Offset += t.Offset; }
		inline void operator-=(const Transformation& t) { Dir -= t.Dir; Offset -= t.Offset; }
		
		inline void operator+=(const godot::Vector3i& offset) { Offset += offset; }
		inline void operator-=(const godot::Vector3i& offset) { Offset -= offset; }
		
		inline void operator+=(Direction dir) { Dir += dir; }
		inline void operator-=(Direction dir) { Dir -= dir; }
		
		
		inline Transformation operator+(const Transformation& t) const { return { .Dir = Dir + t.Dir, .Offset = Offset + t.Offset }; }
		inline Transformation operator-(const Transformation& t) const { return { .Dir = Dir - t.Dir, .Offset = Offset - t.Offset }; }
		
		inline Transformation operator+(const godot::Vector3i& offset) const { return { .Dir = Dir, .Offset = Offset + offset }; }
		inline Transformation operator-(const godot::Vector3i& offset) const { return { .Dir = Dir, .Offset = Offset - offset }; }
		
		inline Transformation operator+(Direction dir) const { return { .Dir = Dir + dir, .Offset = Offset }; }
		inline Transformation operator-(Direction dir) const { return { .Dir = Dir - dir, .Offset = Offset }; }
		
		
	public:
		godot::Vector3i apply(godot::Vector3i target) const;
		
		
	public:
		static const Transformation ZERO;
	};
	
	
	inline static godot::Vector3i operator*(const godot::Vector3i& v, const Transformation& t) 
	{
		return v * t.Dir + t.Offset;
	}
}


#endif