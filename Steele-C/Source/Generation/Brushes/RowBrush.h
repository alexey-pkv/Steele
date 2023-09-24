#ifndef STEELE_ROWBRUSH_H
#define STEELE_ROWBRUSH_H


#include "Base/Generation/IBrush.h"
#include "DataTypes/Generation/Palette/BrushPalette.h"


namespace Steele
{
	class RowBrush : public AbstractBrush<BrushType::Row>
	{
	private:
		int m_maxHeight;
		int m_minHeight;
		int m_paletteID;
		
		
	private:
		bool filter_brushes(const IBrush* brush) const;
		void get_brushes_palette(BrushPalette& bp, IGenerationScope& scope) const;
		Area paint_one_side(IGenerationScope& scope, const Area& area) const;
		
		
	public: // AbstractBrush
		bool can_fill(const Area& a) const override;
		void paint(IGenerationScope& scope, const Area& area) const override;
	};
}


#endif