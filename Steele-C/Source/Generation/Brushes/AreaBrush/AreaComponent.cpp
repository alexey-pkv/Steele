#include "AreaComponent.h"


#include <utility>

#include "Base/Generation/IGenerationScope.h"


Steele::AreaComponent::AreaComponent(Steele::Area area) : 
	m_area(std::move(area))
{
	
}

Steele::AreaComponent::AreaComponent(Steele::Area area, string name) : 
	m_area(std::move(area))
{
	set_name(std::move(name));
}

void Steele::AreaComponent::paint_in_area(Steele::IGenerationScope& scope) const
{
	auto& map = scope.map();
	
	map.push_transformation(m_area.offset(), m_direction);
	
	if (m_area.offset() == v2i_zero)
	{
		paint(scope, m_area);
	}
	else
	{
		paint(scope, m_area.get_reset_offset_area());
	}
}

void Steele::AreaComponent::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	t_id brushID;
	
	if (m_brushID != NULL_ID)
	{
		brushID = m_brushID;
	}
	else if (m_paletteID != NULL_ID)
	{
		auto palette = scope.palette_db().require(m_paletteID);
		brushID = palette->brushes().select_random(scope.rng());
		
		if (brushID == NULL_ID)
		{
			throw PaintException("No brush found in palette");
		}
	}
	else
	{
		throw PaintException("Brush or Palette ID must be set");
	}
	
	auto brush = scope.brush_db().require(brushID);
	brush->paint(scope, area);
}
