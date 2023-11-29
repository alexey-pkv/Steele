#ifndef STEELE_IGENERATIONMAP_H
#define STEELE_IGENERATIONMAP_H


#include "Generation/Map/ITransformable.h"
#include "Base/Map/IStackableMap.h"
#include "DataTypes/Map/Cell.h"
#include "Base/Map/IMap.h"

namespace Steele
{
	template<typename CELL>
	class IGenerationMap :
		public IMap<CELL>,
		public ITransformable
	{
		
	};
	
	
	typedef IGenerationMap<Cell> IGenerationWorldMap;
}


#endif