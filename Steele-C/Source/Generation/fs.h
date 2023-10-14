#ifndef STEELE_FS_H
#define STEELE_FS_H


#include "json.h"


namespace Steele::fs
{
	void save_json(const json& json, const char* path);
	void load_json(json& json, const char* path);
	
	ItemType load_type(const char* path);
	ItemType require_type(const char* path);
}


#endif