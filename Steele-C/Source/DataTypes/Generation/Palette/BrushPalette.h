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
		
		
	private:
		static const IBrush* select_random(const std::map<t_id, float>& from, IGenerationScope& scope, const Area& a) ;
		
		
	public:
		const IBrush* select_random(IGenerationScope& scope, const Area& a) const;
		const IBrush* select_random_where(IGenerationScope& scope, const Area& a, std::function<bool(IBrush*)>& lambda) const;
		void reduce_palette(BrushPalette& p, IGenerationScope& scope, std::function<bool(IBrush*)>& where) const;
	};
}


#endif