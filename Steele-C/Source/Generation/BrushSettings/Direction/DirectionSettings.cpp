#include "DirectionSettings.h"


Steele::Direction Steele::DirectionSettings::get(Steele::IRNG& rng) const
{
	switch (SettingType)
	{
		case Type::Homogeneous:
			return Direction(rng.next_int_32(0, 3) * 2);
		
		case Type::Constant:
			return ConstantDirection;
			
		case Type::Variable:
			return Direction(rng.next_index(VariableDirection, 4) * 2);
			
		default:
			return Direction::North;
	}
}

void Steele::DirectionSettings::json_write(nlohmann::json& into) const
{
	switch (SettingType)
	{
		case Type::Variable:
			into = VariableDirection;
			break;
			
		case Type::Constant:
			into = ConstantDirection;
			break;
			
		case Type::Homogeneous:
		default:
			into = nlohmann::json::object();
			break;
	}
}

void Steele::DirectionSettings::json_read(nlohmann::json& from)
{
	ConstantDirection = Direction::North;
	
	VariableDirection[0] = 1;
	VariableDirection[1] = 1;
	VariableDirection[2] = 1;
	VariableDirection[3] = 1;
	
	if (from.is_string())
	{
		SettingType = Type::Constant;
		
		ConstantDirection = from.get<Direction>();
	}
	else if (from.is_array() && from.size() == 4)
	{
		SettingType = Type::Variable;
		
		VariableDirection[0] = from[0].get<float>();
		VariableDirection[1] = from[1].get<float>();
		VariableDirection[2] = from[2].get<float>();
		VariableDirection[3] = from[3].get<float>();
	}
	else
	{
		SettingType = Type::Homogeneous;
	}
}
