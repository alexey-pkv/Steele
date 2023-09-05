#include "FillBrush.h"


void Steele::FillBrush::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	if (m_groundID == NULL_ID && m_paletteID == NULL_ID)
		throw MisconfiguredBrushException("One of Ground ID or Palette ID must be set for a Fill Brush");
	if (area.is_empty())
		return;
	
	Direction	dir;
	Cell*		cell;
	t_id		groundID = m_groundID;
	Palette*	palette = nullptr;
	
	auto& map = scope.map();
	auto& rng = scope.rng();
	
	if (groundID == NULL_ID)
	{
		palette = scope.get_pallet(m_paletteID);
		
		if (palette == nullptr)
		{
			throw NoPaletteException();
		}
		else if (palette->ground().is_empty())
		{
			throw NoGroundInPaletteException();
		}
	}
	
	for (auto v : area)
	{
		dir = m_dir.get(rng);
		cell = map.get(v);
		
		if (palette)
		{
			groundID = palette->ground().select_random(rng);
		}
		
		cell->Ground.set(groundID, dir, 0);
	}
}
