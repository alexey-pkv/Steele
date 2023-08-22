#ifndef STEELE_WORLDMAP_H
#define STEELE_WORLDMAP_H


#include "Components/Cell.h"
#include "DataTypes/GenericMap.h"
#include "DataTypes/TransformationStack.h"

#include <map>


namespace Steele
{
	class WorldMap : public GenericMap<Cell>
	{
	public:
		WorldMap() = default;
		~WorldMap() = default;
	};
}


#endif