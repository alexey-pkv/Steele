#include "DirectionSettings.h"


Steele::Direction Steele::DirectionSettings::get(Steele::RNG::IRNG& rng) const
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
