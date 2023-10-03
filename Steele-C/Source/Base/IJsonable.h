#ifndef STEELE_IJSONABLE_H
#define STEELE_IJSONABLE_H


#include "json.hpp"
#include "DataTypes/Types.h"
#include "DataTypes/Direction.h"


namespace Steele
{
	class IJsonable
	{
	public:
		virtual void json_read(const nlohmann::json& json) = 0;
		virtual nlohmann::json json_write() const = 0;
	};
	
	
	nlohmann::json json_write(const v2i& t);
	void json_read(const nlohmann::json& json, v2i& into, const v2i& def = v2i_zero);
	
	nlohmann::json json_write(const v3i& t);
	void json_read(const nlohmann::json& json, v3i& into, const v3i& def = v3i_zero);
	
	nlohmann::json json_write(const v2& t);
	void json_read(const nlohmann::json& json, v2& into, const v2& def = v2_zero);
	
	nlohmann::json json_write(const v3& t);
	void json_read(const nlohmann::json& json, v3& into, const v3& def = v3_zero);
	
	
	template<class T>
	T json_read(const nlohmann::json& json)
	{
		T t;
		json_read(json, t);
		return t;
	}
	
	template<class T>
	T json_read(const nlohmann::json& json, const T& def)
	{
		T t;
		json_read(json, t, def);
		return t;
	}
	
	template<class T>
	void json_write(nlohmann::json& json, const std::string& key, const T& t)
	{
		json[key] = json_write(t);
	}
	
	template<class T>
	void json_write(nlohmann::json& json, const char* key, const T& t)
	{
		json[key] = json_write(t);
	}
}


#endif
