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
		
		virtual void set_rng_state(const RandomState& state) = 0;
		virtual void using_map(IMap<Cell>* map) = 0;
		
		virtual void validate_abort() = 0;
		virtual float get_progress() const = 0;
		virtual void abort() = 0;
		
		virtual bool generate() = 0;
		virtual bool generate(IBrush& brush, const Area& area) = 0;
		
		virtual void reset_generation() = 0;
	};
}


#endif