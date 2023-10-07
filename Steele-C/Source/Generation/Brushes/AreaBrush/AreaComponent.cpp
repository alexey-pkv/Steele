#include "AreaComponent.h"


#include <utility>

#include "Base/Generation/IGenerationScope.h"
#include "Exceptions/JSONException.h"


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
	const IBrush* brush;
	
	if (m_brushID != NULL_ID)
	{
		brush = scope.brush_db().require(m_brushID);
	}
	else if (m_paletteID != NULL_ID)
	{
		auto palette = scope.palette_db().require(m_paletteID);
		brush = palette->brushes().select_random(scope, area);
	}
	else
	{
		throw PaintException("Brush or Palette ID must be set");
	}
	
	brush->paint(scope, area);
}

bool Steele::AreaComponent::can_fill(const Steele::Area& a) const
{
	return m_area == a;
}


void Steele::AreaComponent::json_write(nlohmann::json& into) const
{
	auto& map = IDMap::global();
	
	into = nlohmann::json::object();
	
	if (m_direction != Direction::North)
	{
		into["dir"] = m_direction;
	};
	
	if (m_brushID != NULL_ID)
	{
		into["brush"] = map.require(m_brushID);
	}
	else if (m_paletteID != NULL_ID)
	{
		into["palette"] = map.require(m_paletteID);
	}
	
	into["area"] = m_area;
}

void Steele::AreaComponent::json_read(const nlohmann::json& from)
{
	auto& map = IDMap::global();
	
	m_paletteID	= NULL_ID;
	m_brushID	= NULL_ID;
	
	m_area.clear();
	m_direction = Direction::North;
	
	if (!from.is_object())
		return;
	
	if (from.contains("palette"))
	{
		m_paletteID = map.require(from["palette"].get<string>());
	}
	else if (from.contains("brush"))
	{
		m_brushID = map.require(from["brush"].get<string>());
	}
	else
	{
		throw JSONException("Either ground or palette must be set!");
	}
	
	m_direction = from["dir"];
	m_area = from["area"];
}
