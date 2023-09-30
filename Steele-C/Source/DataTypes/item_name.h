#ifndef STEELE_ITEM_NAME_H
#define STEELE_ITEM_NAME_H


#include <string>


namespace Steele
{
	enum class ItemType : int
	{
		Text			= 0,
		Image			= 1,
		
		Brush_Fill		= 1000,
		Brush_Canvas	= 1001,
		Brush_Area		= 1002,
		
		Palette			= 2000
	};
	
	
	const std::string& get_type_name(ItemType type);
	std::string get_name(const std::string& module, ItemType type, const std::string& fullPath); 
}


#endif

