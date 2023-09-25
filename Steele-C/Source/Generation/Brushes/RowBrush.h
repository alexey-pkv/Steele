#ifndef STEELE_ROWBRUSH_H
#define STEELE_ROWBRUSH_H


#include "Base/Generation/IBrush.h"
#include "DataTypes/Generation/Palette/BrushPalette.h"


namespace Steele
{
	class RowBrush : public AbstractBrush<BrushType::Row>
	{
	private:
		int m_maxHeight	= 0;
		int m_minHeight = 0;
		t_id m_paletteID = 0;
		
		
	private:
		bool filter_brushes(const IBrush* brush) const;
		void get_filtered_brushes_palette(BrushPalette& bp, IGenerationScope& scope) const;
		Area paint_one_side(IGenerationScope& scope, const Area& area) const;
		
		
	public: // AbstractBrush
		bool can_fill(const Area& a) const override;
		void paint(IGenerationScope& scope, const Area& area) const override;
		
		
	public:
		int get_min_height() const { return m_minHeight; }
		void set_min_height(int min) { m_minHeight = min; }
		
		int get_max_height() const { return m_maxHeight; }
		void set_max_height(int max) { m_maxHeight = max; }
		
		t_id get_palette_id() const { return m_paletteID; }
		void set_palette_id(t_id id) { m_paletteID = id; }
	};
}


#endif