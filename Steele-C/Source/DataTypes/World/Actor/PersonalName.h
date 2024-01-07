#ifndef STEELE_PERSONALNAME_H
#define STEELE_PERSONALNAME_H


#include <string>


namespace Steele
{
	struct PersonalName
	{
	public:
		std::string First;
		std::string Middle;
		std::string Last;
		std::string Alias;
		
		
	public:
		~PersonalName() = default;
		PersonalName() = default;
		PersonalName(const PersonalName&) = default;
		PersonalName(PersonalName&&) = default;
		PersonalName& operator=(const PersonalName&) = default;
		PersonalName& operator=(PersonalName&&) = default;
		
		
	public:
		inline bool has_alias() const { return !Alias.empty(); }
		inline bool has_middle_name() const { return !Middle.empty(); }
		inline std::string full_name() const
		{
			if (has_middle_name())
				return First + " " + Middle + " " + Last;
			else
				return First + " " + Last;
		}
	};
}


#endif