#include "fs.h"
#include "Exceptions/JSONException.h"

#include <fstream>


using namespace std;
using namespace Steele;


const char* KEY_ITEM_TYPE	= "item_type";


void Steele::fs::save_json(const json& json, const char* path)
{
	std::ofstream stream(path);
	
	if (!stream.is_open())
	{
		throw JSONException("Failed to open file: ", path);
	}
	
	try
	{
		stream << json;
	}
    catch(const std::exception& e)
    {
		throw JSONException("Failed to write to file: ", path, ", error: ", e.what());
    }
}

void Steele::fs::load_json(json& json, const char* path)
{
	std::ifstream stream(path);
	
	json.clear();
	
	if (!stream.is_open())
    {
		throw JSONException("Failed to open file: ", path);
    }
	
	try
    {
        stream >> json;
    }
    catch(const std::exception& e)
    {
		throw JSONException("Failed to read file: ", path, ", error: ", e.what());
    }
}


ItemType Steele::fs::load_type(const char* path)
{
	json j;
	
	load_json(j, path);
	
	if (!j.is_object() || !j.contains(KEY_ITEM_TYPE) || !j[KEY_ITEM_TYPE].is_string())
		return ItemType::Invalid;
	
	return j[KEY_ITEM_TYPE].get<ItemType>();
}


ItemType Steele::fs::require_type(const char* path)
{
	auto type = load_type(path);
	
	if (type == ItemType::Invalid)
		throw JSONException("Could not read item type in: ", path);
	
	return type;
}