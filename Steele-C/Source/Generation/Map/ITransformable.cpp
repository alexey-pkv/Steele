#include "ITransformable.h"


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

bool Steele::LocalTransformation::is_transformed() const
{
	return m_isApplied;
}

const Steele::Transformation& Steele::LocalTransformation::transformation() const
{
	return m_t;
}


void Steele::AbstractTransformable::_push_transformation(const Steele::Transformation &t)
{
	m_stack.push(t);
}


void Steele::AbstractTransformable::pop_transformation() 
{
	if (!m_stack.pop()) throw NoTransformationException();
}

void Steele::AbstractTransformable::reset_transformation() 
{
	m_stack.clear(); 
}

bool Steele::AbstractTransformable::is_transformed() const 
{
	return m_stack.size() > 0; 
}

Steele::Transformation Steele::AbstractTransformable::peek_transformation() const 
{
	return m_stack.top(); 
}

const Steele::Transformation& Steele::AbstractTransformable::transformation() const
{
	return m_stack.current(); 
}

Steele::LocalTransformation Steele::ITransformable::local_transform()
{
	return { this };
}

Steele::LocalTransformation Steele::ITransformable::local_transform(const Steele::Transformation &t)
{
	return { this, t };
}
