#include "ITransformable.h"


void Steele::LocalTransformation::_push_transformation(const Steele::Transformation& t)
{
	if (m_isApplied)
	{
		auto current = m_source->peek_transformation();
		
		current += t;
		
		m_source->pop_transformation();
		m_source->push_transformation(t);
	}
	else
	{
		m_isApplied = true;
		m_source->push_transformation(t);
	}
}

Steele::LocalTransformation::~LocalTransformation()
{
	if (!m_isApplied)
		return;
	
	m_source->pop_transformation();
	
	m_isApplied = false;
	m_source = nullptr;
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


void Steele::LocalTransformation::pop_transformation()
{
	if (m_isApplied)
	{
		m_isApplied = false;
		m_source->pop_transformation();
	}
}

void Steele::LocalTransformation::reset_transformation()
{
	if (m_isApplied)
	{
		m_isApplied = false;
		m_source->pop_transformation();
	}
}

bool Steele::LocalTransformation::is_transformed() const
{
	return m_isApplied;
}

Steele::Transformation Steele::LocalTransformation::peek_transformation() const
{
	return (m_isApplied ? 
		m_source->peek_transformation() :
		Transformation {});
}

const Steele::Transformation& Steele::LocalTransformation::transformation() const
{
	if (m_source == nullptr)
	{
		return Transformation::ZERO;
	}
	else
	{
		return m_source->transformation();
	}
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