#ifndef STEELE_TYPE_H
#define STEELE_TYPE_H


#include <cstdint>
#include <algorithm>

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3i.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/rect2i.hpp>

#include "json.hpp"


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


const std::string STRING_EMPTY;


namespace Steele
{
	enum class BrushType
	{
		Fill	= 0,
		Canvas	= 1,
		Area	= 2,
		Block	= 3,
		Row		= 4,
		
		AreaComponent	= 100,
		
		Invalid = -1
	};
	
	NLOHMANN_JSON_SERIALIZE_ENUM(BrushType, {
		{ BrushType::Fill,			"Fill" },
		{ BrushType::Canvas,		"Canvas" },
		{ BrushType::Area,			"Area" },
		{ BrushType::Block,			"Block" },
		{ BrushType::Row,			"Row" },
		{ BrushType::AreaComponent,	"AreaComponent" },
		
		{ BrushType::Invalid,	nullptr },
	})
	
	
	enum class ItemType : int
	{
		Invalid		= -1,
		
		Text		= 0, 
		Image		= 1,
		Palette		= 2,
		
		BrushFill	= 100,
		BrushCanvas	= 101,
		BrushArea	= 102,
		BrushRow	= 103,
		BrushBlock	= 104
	};



	const std::multimap<ItemType, std::string>	TYPE_NAMES = {
		{ ItemType::Text,		"Text" },
		{ ItemType::Image,		"Image" },
		{ ItemType::Palette,		"Palette" },
		{ ItemType::BrushFill,	"BrushFill" },
		{ ItemType::BrushCanvas,	"BrushCanvas" },
		{ ItemType::BrushArea,	"BrushArea" },
		{ ItemType::BrushRow,	"BrushRow" },
		{ ItemType::BrushBlock,	"BrushBlock" }	
	};
	
	const std::multimap<std::string, ItemType>	TYPE_NAMES_R = {
		{ "Text",		ItemType::Text },
		{ "Image",		ItemType::Image },
		{ "Palette",		ItemType::Palette },
		{ "BrushFill",	ItemType::BrushFill },
		{ "BrushCanvas",	ItemType::BrushCanvas },
		{ "BrushArea",	ItemType::BrushArea },
		{ "BrushRow",	ItemType::BrushRow },
		{ "BrushBlock",	ItemType::BrushBlock }	
	};
	
	
	inline const std::string& get_name_by_type(ItemType type)
	{
		auto it = TYPE_NAMES.find(type);
		return it == TYPE_NAMES.end() ? STRING_EMPTY : it->second;
	}
	
	inline ItemType get_type_by_name(std::string& name)
	{
		auto it = TYPE_NAMES_R.find(name);
		return it == TYPE_NAMES_R.end() ? ItemType::Invalid : it->second;
	}
	
	
	NLOHMANN_JSON_SERIALIZE_ENUM(ItemType, {
		{ ItemType::Invalid,		nullptr }, 
		
		{ ItemType::Text,			"Text" },
		{ ItemType::Image,			"Image" },
		{ ItemType::Palette,		"Palette" },
		
		{ ItemType::BrushFill,		"BrushFill" },
		{ ItemType::BrushCanvas,	"BrushCanvas" },
		{ ItemType::BrushArea,		"BrushArea" },
		{ ItemType::BrushRow,		"BrushRow" },
		{ ItemType::BrushBlock,		"BrushBlock" }
	})
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


inline v2i v3i_xy(const v3i& v) { return { v.x, v.y }; }
inline v2i v3i_yz(const v3i& v) { return { v.y, v.z }; }
inline v2i v3i_xz(const v3i& v) { return { v.x, v.z }; }

inline v3i to_v3i(const v2i& v) { return { v.x, v.y, 0 }; }
inline v3i to_v3i(const v2i& v, int z) { return { v.x, v.y, z }; }


#endif
