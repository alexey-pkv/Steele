#include "IJsonable.h"
#include "DataTypes/Types.h"


using namespace nlohmann;


json Steele::json_write(const v2i& t)
{
	return json { t.x, t.y };
}

void Steele::json_read(const json& json, v2i& into, const v2i& def)
{
	into = def;
	
	if (!json.is_array() || json.size() != 2)
		return;
	
	into.x = json[0].is_number() ? json[0].get<int>() : 0;
	into.y = json[1].is_number() ? json[1].get<int>() : 0;
}


json Steele::json_write(const v2& t)
{
	return json { t.x, t.y };
}

void Steele::json_read(const json& json, v2& into, const v2& def)
{
	into = def;
	
	if (!json.is_array() || json.size() != 2)
		return;
	
	into.x = json[0].is_number() ? json[0].get<float>() : 0.0f;
	into.y = json[1].is_number() ? json[1].get<float>() : 0.0f;
}


json Steele::json_write(const v3i& t)
{
	return json { t.x, t.y, t.z };
}

void Steele::json_read(const json& json, v3i& into, const v3i& def)
{
	into = def;
	
	if (!json.is_array() || json.size() != 3)
		return;
	
	into.x = json[0].is_number() ? json[0].get<int>() : 0;
	into.y = json[1].is_number() ? json[1].get<int>() : 0;
	into.z = json[2].is_number() ? json[2].get<int>() : 0;
}


json Steele::json_write(const v3& t)
{
	return json { t.x, t.y, t.z };
}

void Steele::json_read(const json& json, v3& into, const v3& def)
{
	into = def;
	
	if (!json.is_array() || json.size() != 3)
		return;
	
	into.x = json[0].is_number() ? json[0].get<float>() : 0.0f;
	into.y = json[1].is_number() ? json[1].get<float>() : 0.0f;
	into.z = json[2].is_number() ? json[2].get<float>() : 0.0f;
}

