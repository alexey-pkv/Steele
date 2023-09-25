#ifndef STEELE_IGENERATIONSCOPE_H
#define STEELE_IGENERATIONSCOPE_H


#include "Base/RNG/IRNG.h"
#include "IGenerationMap.h"
#include "DataTypes/Generation/Palette.h"
#include "Base/Generation/DB/IPatetteDB.h"
#include "Base/Generation/DB/IBrushDB.h"
#include "Base/RNG/IStateRNG.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual IRNG& rng() = 0;
		virtual IStateRNG& rng_state() = 0;
		virtual const IStateRNG& rng_state() const = 0;
		virtual IGenerationWorldMap& map() = 0;
		virtual const IGenerationWorldMap& map() const = 0;
		
		virtual IPaletteDB& palette_db() = 0;
		virtual IBrushDB& brush_db() = 0;
	};
}


#endif