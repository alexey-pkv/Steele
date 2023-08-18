#include "Cell.h"


void Steele::Cell::AddGroundTile(const Steele::GroundTile &tile)
{
	for (auto& g : Ground)
	{
		if (g.ID == tile.ID)
		{
			g.Dir = tile.Dir;
			return;
		}
	}
	
	Ground.push_back(tile);
}

bool Steele::Cell::RemoveGroundTile(const Steele::GroundTile &tile)
{
	for (auto i = 0; i < Ground.size(); i++)
	{
		if (Ground[i].ID != tile.ID)
		{
			Ground.erase(Ground.begin() + i);
			return true;
		}
	}
	
	return false;
}

void Steele::Cell::operator*=(Steele::Direction dir)
{
	RoadOffset = RoadOffset * dir;
}
