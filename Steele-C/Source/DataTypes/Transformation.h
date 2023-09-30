#ifndef STEELE_TRANSFORMATION_H
#define STEELE_TRANSFORMATION_H



#include "godot_cpp/variant/vector3i.hpp"
#include "DataTypes/Direction.h"
#include "Types.h"


namespace Steele
{
	struct Transformation
	{
	public:
		Direction	Dir		= Direction::North;
		v3i			Offset	= v3i_zero;
	
	
	public:
		Transformation() = default;
		Transformation(const Transformation&) = default;
		Transformation(Transformation&&) = default;
		Transformation& operator=(const Transformation&) = default;
		Transformation& operator=(Transformation&&) = default;
		
		Transformation(v3i offset, Direction dir);
		Transformation(v3i offset);
		Transformation(v2i offset, Direction dir);
		Transformation(v2i offset);
		Transformation(Direction dir);
	
		
	public:
		inline void operator+=(const Transformation& t) { *this = *this + t; }
		inline void operator-=(const Transformation& t) { *this = *this - t; }
		
		inline void operator+=(const v3i& offset) { *this = *this + offset; }
		inline void operator-=(const v3i& offset) { *this = *this - offset; }
		inline void operator+=(const v2i& offset) { *this = *this + v3i(offset.x, offset.y, 0); }
		inline void operator-=(const v2i& offset) { *this = *this - v3i(offset.x, offset.y, 0); }
		
		inline void operator+=(Direction dir) { *this = *this + dir; }
		inline void operator-=(Direction dir) { *this = *this - dir; }
		
		
		inline Transformation operator+(const Transformation& t) const { return { Offset + t.Offset * Dir, Dir + t.Dir }; }
		inline Transformation operator-(const Transformation& t) const { return { Offset - t.Offset * (Dir - t.Dir), Dir - t.Dir }; }
		
		inline Transformation operator+(const v3i& offset) const { return { Offset + offset * Dir, Dir }; }
		inline Transformation operator-(const v3i& offset) const { return { Offset - offset * Dir, Dir }; }
		
		inline Transformation operator+(Direction dir) const { return { Offset, Dir + dir }; }
		inline Transformation operator-(Direction dir) const { return { Offset, Dir - dir }; }
		
		inline bool operator==(const Transformation& t) const { return Offset == t.Offset && Dir == t.Dir; }
		inline bool operator!=(const Transformation& t) const { return Offset != t.Offset || Dir != t.Dir; }
		
		
	public:
		v3i apply(v3i target) const;
		void apply_ref(v3i& target) const;
		
		
	public:
		static const Transformation ZERO;
	};
	
	
	inline static v3i operator*(const v3i& v, const Transformation& t) 
	{
		return v * t.Dir + t.Offset;
	}
}


#endif