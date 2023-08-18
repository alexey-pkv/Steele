#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Palette.h"
#include "RNG/IRNG.h"
#include "Map/WorldMap.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual RNG::IRNG& RNG() = 0;
		virtual WorldMap& Map() = 0;
		virtual const WorldMap& Map() const = 0;
		
		virtual sptr<Palette> GetPalette(t_id id) = 0;
	};
}


#endif