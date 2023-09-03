#include "Cell.h"


Steele::Cell::Cell(const Steele::GroundTile& gt)
{
	Ground.add(gt);
}

Steele::Cell::Cell(t_id id, Steele::Direction d, uint8_t index)
{
	Ground.add(id, d, index);
}
