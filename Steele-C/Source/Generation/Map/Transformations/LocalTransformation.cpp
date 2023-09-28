#include "LocalTransformation.h"


#include "Generation/Map/ITransformable.h"


void Steele::LocalTransformation::set_transformation(const Steele::Transformation& t)
{
	m_t = t;
	
	if (m_isApplied)
	{
		m_source->pop_transformation();
		m_source->push_transformation(m_t);
	}
	else
	{
		m_isApplied = true;
		m_source->push_transformation(m_t);
	}
}

Steele::LocalTransformation::~LocalTransformation()
{
	if (!m_isApplied)
		return;
	
	m_source->pop_transformation();
}

Steele::LocalTransformation::LocalTransformation(Steele::LocalTransformation&& source) noexcept : 
	m_isApplied(source.m_isApplied),
	m_source(source.m_source),
	m_t(source.m_t)
{
	source.m_source = nullptr;
	source.m_isApplied = false;
}

Steele::LocalTransformation::LocalTransformation(Steele::ITransformable* parent) : 
	m_source(parent),
	m_isApplied(false)
{
	
}

Steele::LocalTransformation::LocalTransformation(Steele::ITransformable& parent) :
	LocalTransformation(&parent)
{
	
}

Steele::LocalTransformation::LocalTransformation(Steele::ITransformable* parent, const Steele::Transformation& t) : 
	m_source(parent),
	m_isApplied(true),
	m_t(t)
{
	m_source->push_transformation(m_t);
}

Steele::LocalTransformation::LocalTransformation(Steele::ITransformable& parent, const Steele::Transformation& t) :
	LocalTransformation(&parent, t)
{
	
}


void Steele::LocalTransformation::reset_transformation()
{
	if (m_isApplied)
	{
		m_isApplied = false;
		m_source->pop_transformation();
		m_t = Transformation::ZERO;
	}
}
