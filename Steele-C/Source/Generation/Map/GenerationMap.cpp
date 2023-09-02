#include "GenerationMap.h"


void Steele::GenerationMap::checkpoint() { m_stacked.checkpoint(); }
void Steele::GenerationMap::rollback() { m_stacked.rollback(); }
void Steele::GenerationMap::commit() { m_stacked.commit(); }
bool Steele::GenerationMap::is_in_checkpoint() const { return m_stacked.is_in_checkpoint(); }
int Steele::GenerationMap::stack_depth() const { return m_stacked.stack_depth(); }

void Steele::GenerationMap::reset_transformation() { m_transformations.clear(); m_transformed.reset_transform(); }
bool Steele::GenerationMap::is_transformed() const { return m_transformations.is_transformed(); }
Steele::Transformation Steele::GenerationMap::peek_transformation() const { return m_transformations.top(); }
const Steele::Transformation& Steele::GenerationMap::transformation() const { return m_transformations.current(); }

void Steele::GenerationMap::_push_transformation(const Steele::Transformation& t)
{
	m_transformations.push(t); 
	m_transformed.set_transformation(m_transformations.current());
}

void Steele::GenerationMap::pop_transformation() 
{
	m_transformations.pop(); 
	m_transformed.set_transformation(m_transformations.current());
}

Steele::GenerationMap::GenerationMap() :
	m_transformed(m_map),
	m_stacked(m_transformed)
{
	
}

void Steele::GenerationMap::clear()
{
	m_stacked.clear();
}

Steele::Cell* Steele::GenerationMap::_try_get(v3i at)
{
	return m_stacked.try_get(at);
}

const Steele::Cell* Steele::GenerationMap::_try_get(v3i at) const
{
	return m_stacked.try_get(at);
}

Steele::Cell* Steele::GenerationMap::_get(v3i at)
{
	return m_stacked.get(at);
}

void Steele::GenerationMap::_set(const Steele::Cell& c, v3i at)
{
	m_stacked.set(c, at);
}

void Steele::GenerationMap::_set(Steele::Cell&& c, v3i at)
{
	m_stacked.set(std::move(c), at);
}

bool Steele::GenerationMap::_is_empty(v3i at) const
{
	return m_stacked.is_empty(at);
}

bool Steele::GenerationMap::_remove(v3i at)
{
	return m_stacked.remove(at);
}
