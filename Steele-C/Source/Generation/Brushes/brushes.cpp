#include "brushes.h"


using namespace Steele;


Direction get_direction(IGenerationScope &gs, const DirectionSettings& ds)
{
	return Direction::NorthEast;
}


void Steele::fill(IGenerationScope &gs, const Area &a, const FillSettings &fs)
{
	auto& map = gs.Map();
	auto& rng = gs.RNG();
	
	auto groundID = fs.GetGroundID();
	auto palletID = fs.GetPaletteID();
	sptr<Palette> pallet = nullptr;
	
	if (palletID)
	{
		pallet = gs.GetPalette(palletID);
	}
	
	for (auto v : a)
	{
		auto tile = GroundTile {};
		
		tile.Dir = get_direction(gs, fs.Direction());
		
		if (groundID)
		{
			tile.ID = groundID;
		}
		else
		{
			tile.ID = pallet->Ground().SelectRandom(rng);
		}
		
		// map.Get(v, 0, true);->AddGroundTile(tile);
	}
}
