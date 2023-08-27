#ifndef STEELE_WORLDMAP_H
#define STEELE_WORLDMAP_H


#include "Base/Map/IMap.h"
#include "DataTypes/Map/Cell.h"
#include "Generation/Map/ITransformable.h"


namespace Steele
{
	class WorldMap :
		public IMap<Cell>,
		public AbstractTransformable
	{
	public:
		WorldMap() = default;
		~WorldMap() = default;
		
	
	protected:
		Cell* _try_get(v3i at) override;
		Cell* _get(v3i at) override;
		bool _is_empty(v3i at) const override;
		bool _remove(v3i at) override;
	
	public:
		void clear() override;
	};
}


#endif