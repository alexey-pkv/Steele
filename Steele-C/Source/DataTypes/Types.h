#ifndef STEELE_TYPE_H
#define STEELE_TYPE_H


#include <cstdint>
#include <algorithm>

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3i.hpp>
#include <godot_cpp/variant/vector3.hpp>


typedef godot::Vector2i v2i;
typedef godot::Vector3i v3i;
typedef godot::Vector2 	v2;
typedef godot::Vector3 	v3;


#define v2_zero		{ 0, 0 }
#define v2i_zero	{ 0, 0 }
#define v3_zero		{ 0, 0, 0 }
#define v3i_zero	{ 0, 0, 0 }


typedef std::uint16_t	t_id;
#define NULL_ID 0


namespace Steele
{
	enum class BrushType
	{
		Fill		= 0,
		Canvas		= 1,
		Template	= 2
	};
}


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


#endif
