#include "RowBrush.h"

#include "Base/Generation/IGenerationScope.h"
#include "Generation/Brushes/Row/combination.h"
#include "Exceptions/JSONException.h"

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

void RowBrush::paint_one_side_local(IGenerationScope& scope, Area& area) const
{
	Area change;
	v3i offset = v3i_zero;
	auto width = area.width();
	
	std::set<int>	sizes;
	
	BrushPalette palette;
	
	get_filtered_brushes_palette(palette, scope);
	get_brush_sizes(scope, palette, sizes);
	
	while (width > 0)
	{
		auto b 		= get_next_brush(scope, palette, sizes, width);
		auto brushArea	= b->get_constant_area();
		auto brushWidth		= brushArea.width();
		
		{
			auto lt = scope.map().local_transform(offset);
			b->paint(scope, area);
		}

#ifdef DEBUG_RowBrush
		cout << "--------------------------------------------------" << endl;
		cout << scope.map().debug_info() << endl;
		cout << "--------------------------------------------------" << endl;
#endif
		
		offset.x += brushWidth;
		width -= brushWidth;
		change += brushArea;
		
		change.add_offset(-brushWidth, 0);
		area.add_offset(-brushWidth, 0);
	}
	
	area.reset_offset();
	change.reset_offset();
	
	area -= change;
}

void RowBrush::paint_one_side_relative(IGenerationScope& scope, Area& area) const
{
	auto offset = area.offset();
	
	area.reset_offset();
	
	{
		auto lt = scope.map().local_transform(offset);
		paint_one_side_local(scope, area);
	}
	
	area.add_offset(offset);
}

void RowBrush::fill(IGenerationScope& scope, Area& area) const
{
	auto fillBrush = scope.brush_db().require(m_fillID);
	
	{
		auto lt = scope.map().local_transform(area.offset());
		
		area.reset_offset();
		
		fillBrush->paint(scope, area);
	}
}


bool RowBrush::can_fill(const Area& a) const
{
	return false;
}

void RowBrush::paint(IGenerationScope& scope, const Area& area) const
{
	if (m_fillID == STEELE_NULL_ID || m_paletteID == STEELE_NULL_ID)
		throw PaintException("Fill ID and Palette ID must be set!");
	
	if (area.height() > area.width())
	{
		auto lt = scope.map().local_transform(Direction::East);
		paint(scope, area * Direction::East);
	}
	else
	{
		Area region = area;
		
		paint_one_side_relative(scope, region);
		auto offset = region.offset();
		
		{
			auto lt = scope.map().local_transform({ area.width() - 1, area.height() - 1 }, Direction::South);
			
			region *= Direction::South;
			region.reset_offset();
			
			paint_one_side_relative(scope, region);
		}
		
		region *= Direction::South;
		region.set_offset(offset);
		
#ifdef DEBUG_RowBrush
		cout << "===================================" << endl;
		cout << scope.map().debug_info() << endl;
		cout << "===================================" << endl;
#endif
		
		fill(scope, region);
	}
}


void RowBrush::json_write(json& into) const
{
	auto& map = IDMap::global();
	
	into = json::object();
	
	into["min_height"] = m_minHeight;
	into["max_height"] = m_maxHeight;
	
	if (m_paletteID != STEELE_NULL_ID)
	{
		into["palette"]	= map.require(m_paletteID);
	}
	else if (m_fillID != STEELE_NULL_ID)
	{
		into["ground"] = map.require(m_fillID);
	}
}

void RowBrush::json_read(const json& from)
{
	auto& map = IDMap::global();
	
	if (from.contains("palette"))
	{
		m_paletteID = map.require(from["palette"].get<string>());
	}
	else if (from.contains("ground"))
	{
		m_fillID = map.require(from["ground"].get<string>());
	}
	else
	{
		throw JSONException("Either ground or palette must be set!");
	}
}
