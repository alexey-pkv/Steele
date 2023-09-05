#include "GenerationScope.h"



Steele::RNG::IRNG& Steele::GenerationScope::rng() { return m_rng;}
Steele::IGenerationWorldMap& Steele::GenerationScope::map() { return m_map; }
const Steele::IGenerationWorldMap& Steele::GenerationScope::map() const { return m_map; }


Steele::GenerationScope::GenerationScope() : m_rng("hello_world")
{
	uint64_t state[] = { 1, 1 };
	
	m_rng.SetState(state);
}

Steele::Palette* Steele::GenerationScope::get_pallet(t_id id)
{
	return get_value_ptr(m_pallets, id);
}

const Steele::Palette* Steele::GenerationScope::get_pallet(t_id id) const
{
	return get_value_ptr(m_pallets, id);
}

bool Steele::GenerationScope::has_pallet(t_id id) const
{
	return contains(m_pallets, id);
}
