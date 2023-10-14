#ifndef STEELE_STEELEID_H
#define STEELE_STEELEID_H


#include <string>
#include "Types.h"


namespace Steele
{
	class SteeleID
	{
	private:
		std::string m_fullName;
		std::string m_module;
		ItemType	m_type;
		std::string	m_path;
		
		
	public:
		SteeleID() = delete;
	
		~SteeleID() = default;
		SteeleID(const SteeleID&) = default;
		SteeleID(SteeleID&&) = default;
		SteeleID& operator=(const SteeleID&) = default;
		SteeleID& operator=(SteeleID&&) = default;
		
		
	public:
		bool operator==(const SteeleID& id);
		bool operator<=(const SteeleID& id);
		bool operator<(const SteeleID& id);
		
		
	public:
		const std::string& full_name() const;
		const std::string& path() const;
		const std::string& short_name() const;
		const std::string& module() const;
		const std::string& type_name() const;
		
		
	public:
		inline bool isBrush() const { return (int)m_type >= 100 && (int)m_type < 200; }
	};
}


#endif