#ifndef STEELE_IGENERATIONSCOPE_H
#define STEELE_IGENERATIONSCOPE_H


#include "RNG/IRNG.h"
#include "IGenerationMap.h"
#include "DataTypes/Generation/Palette.h"


namespace Steele
{
	class IGenerationScope
	{
	public:
		virtual RNG::IRNG& rng() = 0;
		virtual IGenerationWorldMap& map() = 0;
		virtual const IGenerationWorldMap& map() const = 0;
		
		virtual Palette* get_pallet(t_id id) = 0;
		virtual const Palette* get_pallet(t_id id) const = 0;
		virtual bool has_pallet(t_id id) const = 0;
	};
}


#endif