#include "Cell.h"

#include "json.h"


Steele::Cell::Cell(const Steele::GroundTile& gt)
{
	Ground.add(gt);
}

Steele::Cell::Cell(t_id id, Steele::Direction d, uint8_t index)
{
	Ground.add(id, d, index);
}


void Steele::Cell::json_write(nlohmann::json& into) const
{
	into = { { "ground", Ground } };
}

void Steele::Cell::json_read(const nlohmann::json& from)
{
	Ground = from["ground"];
}
