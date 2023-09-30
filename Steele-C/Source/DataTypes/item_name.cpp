#include "item_name.h"
#include "Exceptions/SteeleException.h"


using namespace std;
using namespace Steele;



const std::string ITEM_TYPE_TEXT			= "Text";
const std::string ITEM_TYPE_IMAGE			= "Image";
const std::string ITEM_TYPE_BRUSH_FILL		= "Brush_Fill";
const std::string ITEM_TYPE_BRUSH_CANVAS	= "Brush_Canvas";
const std::string ITEM_TYPE_BRUSH_AREA		= "Brush_Area";
const std::string ITEM_TYPE_PALETTE			= "Palette";

const std::string DIVIDER	= ":";



string Steele::get_name(const string& module, ItemType type, const string& fullPath)
{
	auto& typeName = get_type_name(type);
	
	string result;
	auto divLength = DIVIDER.length();
	
	result.reserve(
		module.length() +
		divLength +
		typeName.length() + 
		divLength + 
		fullPath.length());
	
	result = module + DIVIDER + typeName + DIVIDER + fullPath;
	
	return result;
}

const std::string& Steele::get_type_name(ItemType type)
{
	switch (type)
	{
		case ItemType::Text:			return ITEM_TYPE_TEXT;
		case ItemType::Image:			return ITEM_TYPE_IMAGE;
		
		case ItemType::Brush_Fill:		return ITEM_TYPE_BRUSH_FILL;
		case ItemType::Brush_Canvas:	return ITEM_TYPE_BRUSH_CANVAS;
		case ItemType::Brush_Area:		return ITEM_TYPE_BRUSH_AREA;
		
		case ItemType::Palette:			return ITEM_TYPE_PALETTE;
		default:
			throw SteeleException("No string name defined for item type ", (int)type);
	}
}
