#ifndef STEELE_TYPE_H
#define STEELE_TYPE_H


#include <cstdint>
#include <algorithm>

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3i.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/rect2i.hpp>


typedef godot::Vector2i v2i;
typedef godot::Vector3i v3i;
typedef godot::Vector2 	v2;
typedef godot::Vector3 	v3;
typedef godot::Rect2i	r2i;


#define v2_zero		v2 { 0, 0 }
#define v2i_zero	v2i { 0, 0 }
#define v3_zero		v3 { 0, 0, 0 }
#define v3i_zero	v3i { 0, 0, 0 }

#define v2_one		v2 { 1, 1 }
#define v2i_one		v2i { 1, 1 }
#define v3_one		v3 { 1, 1, 1 }
#define v3i_one		v3i { 1, 1, 1 }
#define v3i_x_one	v3i { 1, 0, 0 }
#define v3i_y_one	v3i { 0, 1, 0 }
#define v3i_z_one	v3i { 0, 0, 1 }



typedef std::int32_t	t_id;
#define NULL_ID 0


typedef unsigned char byte;


namespace Steele
{
	enum class BrushType : char
	{
		Fill	= 0,
		Canvas	= 1,
		Area	= 2,
		Row		= 3,
		
		AreaComponent	= 100
	};
}

enum class Axis
{
	X,
	Y
};


#define SORT_BY_FIELD_REF(source, type, field)		\
	std::sort(										\
		source.begin(),								\
		source.end(),								\
		[](type a, type b)							\
		{											\
			return a.field < b.field;				\
		})

#define SORT_BY_FIELD_PTR(source, type, field)		\
	std::sort(										\
		source.begin(),								\
		source.end(),								\
		[](type a, type b)							\
		{											\
			return a->field < b->field;				\
		})


inline v2i abs(const v2i& v) { return { abs(v.x), abs(v.y) }; }
inline v3i to_v3i(v2i v) { return { v.x, v.y, 0 }; }

#endif
