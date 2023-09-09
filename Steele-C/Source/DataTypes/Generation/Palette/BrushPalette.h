#ifndef STEELE_BRUSHPALETTE_H
#define STEELE_BRUSHPALETTE_H


#include "DataTypes/Area.h"
#include "Base/Generation/IBrush.h"
#include "Palettes.h"


namespace Steele
{
	class BrushPalette : public ScalarPalette<t_id>
	{
	public:
		~BrushPalette() override = default;
		
		BrushPalette() = default;
		BrushPalette(const BrushPalette& s) = default;
		BrushPalette(BrushPalette&& s) noexcept = default;
		BrushPalette& operator=(const BrushPalette&) = default;
		BrushPalette& operator=(BrushPalette&&) = default;
		
		
	public:
		const IBrush* select_random(IGenerationScope& scope , const Area& a) const;
	};
}


#endif