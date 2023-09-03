#ifndef STEELE_IGENERATIONSCOPE_H
#define STEELE_IGENERATIONSCOPE_H


#include "RNG/IRNG.h"
#include "IGenerationMap.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual RNG::IRNG& rng() = 0;
		virtual IGenerationWorldMap& map() = 0;
		virtual const IGenerationWorldMap& map() const = 0;
	};
}


#endif