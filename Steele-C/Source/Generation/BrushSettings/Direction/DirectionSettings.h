#ifndef STEELE_DIRECTIONSETTINGS_H
#define STEELE_DIRECTIONSETTINGS_H


#include "godot_cpp/variant/string.hpp"
#include "DataTypes/Direction.h"
#include "Base/RNG/IRNG.h"


namespace Steele
{
	struct DirectionSettings
	{
	public:
		enum class Type : char 
		{
			// Select randomly one direction out of the main 4.
			Homogeneous,
			
			// Select direction based on weight
			Variable,
			
			// Use a constant direction
			Constant
		};
		
		
	public:
		Type		SettingType				= Type::Homogeneous;
		Direction	ConstantDirection		= Direction::North;
		float 		VariableDirection[4]	= {1, 1, 1, 1};
		
		
	public:
		Direction get(IRNG& rng) const;
	};
}


#endif