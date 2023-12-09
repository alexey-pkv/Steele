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
		inline static const IBrush* select_random(const std::map<t_id, float>& from, IGenerationScope& scope, const Area& a) { return select_random(from, scope, &a); }
		static const IBrush* select_random(const std::map<t_id, float>& from, IGenerationScope& scope, const Area* a) ;
		
		
	public:
		const IBrush* select_random(IGenerationScope& scope) const;
		const IBrush* select_random(IGenerationScope& scope, const Area& a) const;
		const IBrush* select_random_where(IGenerationScope& scope, const Area& a, std::function<bool(const IBrush*)>& lambda) const;
		void get_reduced_palette(BrushPalette& p, IGenerationScope& scope, std::function<bool(const IBrush*)>& where) const;
		void reduce_palette(IGenerationScope& scope, std::function<bool(const IBrush*)>& where);
		
		
	public:
		inline const std::map<t_id, float>& brushes() const { return palette(); }
	};
}


#endif