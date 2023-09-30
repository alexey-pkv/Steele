#include "AreaTransformation.h"


#include "Generation/Map/ITransformable.h"


using namespace Steele;


AreaTransformation::~AreaTransformation()
{
	reset_transformation();
}

AreaTransformation::AreaTransformation(AreaTransformation&& source) noexcept : 
	m_source(source.m_source),
	m_area(source.m_area),
	m_isApplied(source.m_isApplied),
	m_offset(source.m_offset),
	m_dir(source.m_dir)
{
	source.m_isApplied = false;
	source.m_source = nullptr;
	source.m_area = nullptr;
}

AreaTransformation& AreaTransformation::operator=(AreaTransformation&& source) noexcept
{
	m_source	= source.m_source;
	m_area		= source.m_area;
	m_isApplied	= source.m_isApplied;
	m_offset	= source.m_offset;
	m_dir		= source.m_dir;
	
	source.m_isApplied = false;
	source.m_source = nullptr;
	source.m_area = nullptr;
	
	return *this;
}

AreaTransformation::AreaTransformation(ITransformable* parent, Area* area) : 
	m_source(parent),
	m_area(area)
{
	
}

AreaTransformation::AreaTransformation(ITransformable* parent, Area* area, v2i v, Direction dir) : 
	m_source(parent),
	m_area(area)
{
	set_transformation(v, dir);
}


void AreaTransformation::set_transformation(const v2i& v, Direction dir)
{
	if (m_area->is_empty() || (dir == Direction::North && v == v2i_zero))
	{
		reset_transformation();
		return;
	}
	else if (dir == m_dir && v == m_offset)
	{
		return;
	}
	
	Transformation change;
	auto areaRotate = dir - m_dir;
	
	change -= m_offset;
	
	if (areaRotate != Direction::North)
	{
		change += m_area->offset();
	
		switch ((int)areaRotate)
		{
			case (int)DirectionValue::North:
				break;
			case (int)DirectionValue::East:
				change += v3i(m_area->width() - 1, 0, 0);
				break;
			case (int)DirectionValue::South:
				change += m_area->dimensions() - v2i_one;
				break;
			case (int)DirectionValue::West:
			default:
				change += v3i(0, m_area->height() - 1, 0);
				break;
		}
		
		change += areaRotate;
		change -= m_area->offset();
	}
	
	// Update transformation
	if (m_isApplied)
	{
		m_source->pop_transformation();
	}
	else
	{
		m_isApplied = true;
	}
	
	m_source->push_transformation(change);
	
	// Update Area
	if (m_offset != v)
	{
		m_area->add_offset(m_offset - v);
	}
	
	if (areaRotate != Direction::North)
	{
		(*m_area) *= areaRotate;
	}
	
	// Update data members
	m_offset = v;
	m_dir = dir;
}

void AreaTransformation::reset_transformation()
{
	if (!m_isApplied)
		return;
	
	m_isApplied = false;
	m_source->pop_transformation();
	
	m_area->add_offset(m_offset);
	*m_area *= (Direction::North - m_dir);
}

Transformation AreaTransformation::transformation() const
{
	return m_source == nullptr ? Transformation::ZERO : m_source->transformation();
}
