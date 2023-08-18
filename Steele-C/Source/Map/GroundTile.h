#ifndef STEELE_GROUNDTILE_H
#define STEELE_GROUNDTILE_H


#include "DataTypes/Types.h"
#include "DataTypes/Direction.h"


namespace Steele
{
	struct GroundTile
	{
	public:
		t_id ID;
		Direction Dir; 
		
		
	public:
		GroundTile() = default;
		GroundTile(const GroundTile&) = default;
		GroundTile(GroundTile&&) = default;
		GroundTile& operator=(const GroundTile&) = default;
		GroundTile& operator=(GroundTile&&) = default;
	};
}


#endif