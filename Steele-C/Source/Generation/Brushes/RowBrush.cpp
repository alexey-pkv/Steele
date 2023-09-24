#include "RowBrush.h"

#include "Base/Generation/IGenerationScope.h"


using namespace Steele;


bool RowBrush::filter_brushes(const IBrush* brush) const
{
	if (!brush->is_constant_area_brush())
		return false;
	
	auto brushHeight = brush->get_constant_area().height();
	
	return 
		brushHeight >= m_minHeight && 
		brushHeight <= m_maxHeight;
}

void RowBrush::get_brushes_palette(BrushPalette& bp, IGenerationScope& scope) const
{
	auto* palette_ref = scope.palette_db().get(m_paletteID);
	
	if (palette_ref == nullptr)
		throw PaintException("Palette ", m_paletteID, " not found");
	
	std::function<bool(const IBrush*)> lambda = [this](const IBrush* b) { return this->filter_brushes(b); };
	palette_ref->brushes().get_reduced_palette(bp, scope, lambda);
	
	if (bp.is_empty())
		throw PaintException("No brushes found for Row Brush in palette ", m_paletteID);
}

Area RowBrush::paint_one_side(IGenerationScope& scope, const Area& area) const
{
	PUSH_TRANSFORM_V(scope.map(), area.offset());
	
	Area target = area.get_reset_offset_area();
	BrushPalette palette;
	
	get_brushes_palette(palette, scope);
	
	
	
	
	// palette.select_random_where(scope, tar)
	
	return area;
}


bool RowBrush::can_fill(const Area& a) const
{
	return false;
}

void RowBrush::paint(IGenerationScope& scope, const Area& area) const
{
	if (area.height() > area.width())
	{
		PUSH_TRANSFORM_DIR(scope.map(), Direction::East);
		paint(scope, area * Direction::East);
	}
	else
	{
		auto a = paint_one_side(scope, area);
		
		PUSH_TRANSFORM_DIR(scope.map(), Direction::South);
		a *= Direction::South;
		
		paint_one_side(scope, a);
	}
}



bool can_be_combined(unsigned int target_number, std::vector<unsigned int> v_numbers)
{
	return false;
	// TODO: return true if target_number can be combined using the sum of the numbers from the vector v_numbers  
}