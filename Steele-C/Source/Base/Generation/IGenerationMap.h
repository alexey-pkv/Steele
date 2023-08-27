#ifndef STEELE_IGENERATIONMAP_H
#define STEELE_IGENERATIONMAP_H


#include "Generation/Map/ITransformable.h"
#include "Base/Map/IStackableMap.h"
#include "DataTypes/Map/Cell.h"


namespace Steele
{
	class IGenerationMap :
		public ITransformable,
		public IStackableMap
	{
	public:
		virtual IMap<Cell>& map() = 0;
	};
}


#endif