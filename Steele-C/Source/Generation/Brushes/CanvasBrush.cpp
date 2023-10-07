#include "CanvasBrush.h"


#include "Base/Generation/IGenerationScope.h"


void Steele::CanvasBrush::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	auto& map = scope.map();
	
	for (const auto& kvp : m_canvas)
	{
		v2i pos = { kvp.first.x, kvp.first.y };
		
		if (!area.contains(pos))
			throw CanvasAreaOutsideOfBoundException(pos);
		
		map.set(kvp.second, pos);
	}
}

bool Steele::CanvasBrush::can_fill(const Steele::Area& a) const
{
	if (a.get_area() != m_canvas.size())
		return false;
	
	for (const auto &[pos, _] : m_canvas)
	{
		if (!a.contains(v2i {pos.x, pos.y}))
		{
			return false;
		}
	}
	
	return true;
}

bool Steele::CanvasBrush::is_constant_area_brush() const
{
	return true;
}

Steele::Area Steele::CanvasBrush::get_constant_area() const
{
	return m_canvas.get_area();
}

void Steele::CanvasBrush::debug_set(const Steele::Area& a, t_id id)
{
	auto& c = canvas();
	
	for (auto v : a)
	{
		c.set(Cell { id, Direction::North, 0 }, v);
	}
}


void Steele::CanvasBrush::json_write(nlohmann::json& into) const
{
	m_canvas.json_write(into);
}

void Steele::CanvasBrush::json_read(const nlohmann::json& from)
{
	m_canvas.json_read(from);
}
