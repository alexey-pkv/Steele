#ifndef STEELE_DIRECTIONSETTINGS_H
#define STEELE_DIRECTIONSETTINGS_H


#include <godot_cpp/variant/string.hpp>

#include "../../../DataTypes/Direction.h"


namespace Steele
{
	struct DirectionSettings
	{
	public:
		enum class Type : char 
		{
			Homogeneous,
			Weighted,
			Constant,
			Variable
		};
		
		
	public:
		Type			SettingType				= Type::Homogeneous;
		Direction		ConstantDirection		= Direction::North;
		float 			VariableDirection[4]	= {1, 1, 1, 1};
	};
}


#endif