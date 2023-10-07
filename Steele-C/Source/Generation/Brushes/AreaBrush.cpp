#include "AreaBrush.h"


#include "Base/Generation/IGenerationScope.h"


bool Steele::AreaBrush::is_valid() const
{
	Area total = {};
	
	for (const auto& a : m_components)
	{
		if (total.overlaps(a.area()))
		{
			return false;
		}
		
		total &= a.area();
	}
	
	return true;
}

Steele::Area Steele::AreaBrush::total_area() const
{
	Area total = {};
	
	for (const auto& c : m_components)
	{
		total &= c.area();
	}
	
	return total;
}

void Steele::AreaBrush::remove_at(int index)
{
	::remove_at(m_components, index);
}

void Steele::AreaBrush::remove_at(int from, int to)
{
	::remove_at(m_components, from, to);
}

void Steele::AreaBrush::add_area(const Steele::Area& a)
{
	m_components.emplace_back(a);
}

void Steele::AreaBrush::add_area(const Steele::Area& a, const string& name)
{
	m_components.emplace_back(a);
	last(m_components).set_name(name);
}

void Steele::AreaBrush::move(int from, int to)
{
	::rotate(m_components, from, to);
}


void Steele::AreaBrush::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	for (auto& component : m_components)
	{
		if (!area.contains(component.area()))
			throw DrawingAreaDoesNotOverlapException();
		
		component.paint_in_area(scope);
	}
}

bool Steele::AreaBrush::can_fill(const Steele::Area& a) const
{
	return get_constant_area() == a;
}

bool Steele::AreaBrush::is_constant_area_brush() const
{
	return true;
}

Steele::Area Steele::AreaBrush::get_constant_area() const
{
	Area total;
	
	for (auto& component : m_components)
	{
		total += component.area();
	}
	
	return total;
}


void Steele::AreaBrush::json_write(nlohmann::json& into) const
{
	into = m_components;
}

void Steele::AreaBrush::json_read(const nlohmann::json& from)
{
	m_components = from;
}
