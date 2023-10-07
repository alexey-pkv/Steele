#ifndef STEELE_JSON_H
#define STEELE_JSON_H


#include "json.hpp"
#include "DataTypes/Types.h"
#include "DataTypes/Direction.h"


namespace Steele
{
	typedef nlohmann::json json;
	
	
	json json_write(const v2i& t);
	void json_read(const json& json, v2i& into, const v2i& def = v2i_zero);
	
	json json_write(const v3i& t);
	void json_read(const json& json, v3i& into, const v3i& def = v3i_zero);
	
	json json_write(const v2& t);
	void json_read(const json& json, v2& into, const v2& def = v2_zero);
	
	json json_write(const v3& t);
	void json_read(const json& json, v3& into, const v3& def = v3_zero);
	
	
	inline v3i json_read_v3i(const json& json, const v3i& def = v3i_zero)
	{
		v3i v;
		json_read(json, v, def);
		return v;
	}
	
	
	template<class T>
	T json_read(const json& json)
	{
		T t;
		json_read(json, t);
		return t;
	}
	
	template<class T>
	T json_read(const json& json, const T& def)
	{
		T t;
		json_read(json, t, def);
		return t;
	}
	
	template<class T>
	void json_write(json& json, const std::string& key, const T& t)
	{
		json[key] = json_write(t);
	}
	
	template<class T>
	void json_write(json& json, const char* key, const T& t)
	{
		json[key] = json_write(t);
	}
	
	
	template<typename T, typename = std::enable_if_t<std::is_invocable_v<decltype(&T::json_read), T&, const json&>>>
	void from_json(const json& json, T& t)
	{
		t.json_read(json);
	}
	
	template<typename T, typename = std::enable_if_t<std::is_invocable_v<decltype(&T::json_write), const T&, json&>>>
	void to_json(json& json, const T& t)
	{
		t.json_write(json);
	}
}


#endif
