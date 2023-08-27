#include "TransformationStack.h"


bool Steele::TransformationStack::pop()
{
	if (m_stack.empty())
		return false;
	
	m_current -= m_stack.top();
	m_stack.pop();
	
	return true;
}

void Steele::TransformationStack::push(const Transformation& t)
{
	m_current += t;
	m_stack.push(t);
}
