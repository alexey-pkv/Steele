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
	if (dir == Direction::North && v == v2i_zero)
	{
		reset_transformation();
		return;
	}
	else if (dir == m_dir && v == m_offset)
	{
		return;
	}
	
	auto mapOffset = v;
	auto areaRotate = m_dir - dir;
	
	
	// Update transformation
	if (m_isApplied)
	{
		m_source->pop_transformation();
	}
	
	m_source->push_transformation(mapOffset, dir);
	
	// Update Area
	m_area->set_offset(v);
	
	if (areaRotate != Direction::North)
	{
		(*m_area) *= areaRotate;
	}
}

void AreaTransformation::reset_transformation()
{
	
}
