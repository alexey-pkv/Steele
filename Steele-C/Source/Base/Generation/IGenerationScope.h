#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "RNG/IRNG.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual RNG::IRNG& RNG() = 0;
		
		// virtual sptr<Palette> GetPalette(t_id id) = 0;
	};
}


#endif