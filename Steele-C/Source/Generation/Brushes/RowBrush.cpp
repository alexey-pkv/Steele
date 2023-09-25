#include "RowBrush.h"

#include "Base/Generation/IGenerationScope.h"
#include "Generation/Brushes/Row/combination.h"

#include <set>


using namespace std;
using namespace Steele;


void reduce_brushes_to_size(IGenerationScope& scope, BrushPalette& bp, const std::set<int>& sizes)
{
	std::function<bool(const IBrush*)> lambda = [&](const IBrush* b) 
	{
		return contains(sizes, b->get_constant_area().width());
	};
	
	bp.reduce_palette(scope, lambda);
}

void get_brush_sizes(IGenerationScope& scope, BrushPalette& bp, std::set<int>& sizes)
{
	auto& db = scope.brush_db();
	
	for (auto [id, _] : bp.brushes())
	{
		auto b = db.require(id);
		sizes.insert(b->get_constant_area().width());
	}
}

const IBrush* get_next_brush(IGenerationScope& scope, BrushPalette& bp, std::set<int>& sizes, int length)
{
	auto b = bp.select_random(scope);
	
	auto width = b->get_constant_area().width();
	auto sizesCount = sizes.size();
	
	to_combination_set(length - width, sizes);
	
	if (sizesCount != sizes.size())
	{
		reduce_brushes_to_size(scope, bp, sizes);
	}
	
	return b;
}


bool RowBrush::filter_brushes(const IBrush* brush) const
{
	if (!brush->is_constant_area_brush())
		return false;
	
	auto area = brush->get_constant_area();
	
	if (area.is_empty())
		return false;
	
	auto brushHeight = area.height();
	
	return 
		brushHeight >= m_minHeight && 
		brushHeight <= m_maxHeight;
}

void RowBrush::get_filtered_brushes_palette(BrushPalette& bp, IGenerationScope& scope) const
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
	auto lt = scope.map().local_transform(area.offset());
	
	Area target				= area.get_reset_offset_area();
	auto width			= target.width();
	std::set<int>	sizes;
	
	BrushPalette palette;
	
	get_filtered_brushes_palette(palette, scope);
	get_brush_sizes(scope, palette, sizes);
	
	while (width > 0)
	{
		auto b 		= get_next_brush(scope, palette, sizes, width);
		auto brushArea	= b->get_constant_area();
		auto brushWidth		= brushArea.width();
		
		b->paint(scope, target);
		
		width -= brushWidth;
		target -= brushArea;
		
		lt.add_transformation(v2i { brushWidth, 0 });
	}
	
	return target;
}


bool RowBrush::can_fill(const Area& a) const
{
	return false;
}

void RowBrush::paint(IGenerationScope& scope, const Area& area) const
{
	auto lt = scope.map().local_transform();
	
	if (area.height() > area.width())
	{
		lt.set_transformation(Direction::East);
		paint(scope, area * Direction::East);
	}
	else
	{
		auto a = paint_one_side(scope, area);
		
		lt.set_transformation(Direction::South);
		a *= Direction::South;
		
		paint_one_side(scope, a);
	}
}

