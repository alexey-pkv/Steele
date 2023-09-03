#include "GenerationScope.h"



Steele::RNG::IRNG& Steele::GenerationScope::rng() { return m_rng;}
Steele::IGenerationWorldMap& Steele::GenerationScope::map() { return m_map; }
const Steele::IGenerationWorldMap& Steele::GenerationScope::map() const { return m_map; }


Steele::GenerationScope::GenerationScope() : m_rng("hello_world")
{
	uint64_t state[] = { 1, 1 };
	
	m_rng.SetState(state);
}