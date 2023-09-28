#include "ITransformable.h"


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
