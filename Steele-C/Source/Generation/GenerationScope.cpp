#include "GenerationScope.h"


#include "Utils.h"


Steele::IRNG& Steele::GenerationScope::rng() { return m_rng;}
Steele::IGenerationWorldMap& Steele::GenerationScope::map() { return m_map; }
const Steele::IGenerationWorldMap& Steele::GenerationScope::map() const { return m_map; }


Steele::IPaletteDB& Steele::GenerationScope::palette_db()
{
	return m_pallets;
}

Steele::IBrushDB& Steele::GenerationScope::brush_db()
{
	return m_brushes;
}
