#ifndef STEELE_IGENERATIONSCOPE_H
#define STEELE_IGENERATIONSCOPE_H


#include "RNG/IRNG.h"
#include "IGenerationMap.h"
#include "DataTypes/Generation/Palette.h"
#include "Base/Generation/DB/IPatetteDB.h"
#include "Base/Generation/DB/IBrushDB.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual RNG::IRNG& rng() = 0;
		virtual IGenerationWorldMap& map() = 0;
		virtual const IGenerationWorldMap& map() const = 0;
		
		virtual IPaletteDB& palette_db() = 0;
		virtual IBrushDB& brush_db() = 0;
	};
}


#endif