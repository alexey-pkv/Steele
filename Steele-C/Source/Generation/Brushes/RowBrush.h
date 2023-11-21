#ifndef STEELE_ROWBRUSH_H
#define STEELE_ROWBRUSH_H


#include "Base/Generation/IBrush.h"
#include "DataTypes/Generation/Palette/BrushPalette.h"


namespace Steele
{
	class RowBrush : public AbstractBrush<BrushType::Block>
	{
	private:
		int m_maxHeight	= 100;
		int m_minHeight	= 1;
		
		t_id m_paletteID	= STEELE_NULL_ID;
		t_id m_fillID		= STEELE_NULL_ID;
		
		
	private:
		bool filter_brushes(const IBrush* brush) const;
		void get_filtered_brushes_palette(BrushPalette& bp, IGenerationScope& scope) const;
		void paint_one_side_local(IGenerationScope& scope, Area& area) const;
		void paint_one_side_relative(IGenerationScope& scope, Area& area) const;
		void fill(IGenerationScope& scope, Area& area) const;
		
		
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
		
		t_id get_fill_id() const { return m_fillID; }
		void set_fill_id(t_id id) { m_fillID = id; }
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const override;
		void json_read(const nlohmann::json& from) override;
	};
}


#endif