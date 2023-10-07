#include "BrushDB.h"



Steele::IBrush* Steele::BrushDB::create(t_id id, BrushType type)
{
	switch (type)
	{
		case BrushType::Area:
			return create_area(id);
			
		case BrushType::Fill:
			return create_fill(id);
			
		case BrushType::Canvas:
			return create_canvas(id);
			
		case BrushType::Row:
			return create_row(id);
			
		default:
			throw SteeleException("Unexpected brush type ", (int)type);
	}
}


Steele::FillBrush* Steele::BrushDB::create_fill(t_id id)		{ return _create_<FillBrush>(id); }
Steele::CanvasBrush* Steele::BrushDB::create_canvas(t_id id)	{ return _create_<CanvasBrush>(id); }
Steele::AreaBrush* Steele::BrushDB::create_area(t_id id)		{ return _create_<AreaBrush>(id); }
Steele::RowBrush* Steele::BrushDB::create_row(t_id id)			{ return _create_<RowBrush>(id); }

bool Steele::BrushDB::has(t_id id)								{ return AbstractDB::has(id); }
Steele::IBrush* Steele::BrushDB::get(t_id id)					{ return AbstractDB::get(id); }
const Steele::IBrush* Steele::BrushDB::get(t_id id) const		{ return AbstractDB::get(id); }
bool Steele::BrushDB::remove(t_id id)							{ return AbstractDB::remove(id); }
Steele::IBrush* Steele::BrushDB::require(t_id id) 				{ return AbstractDB::require(id); }
const Steele::IBrush* Steele::BrushDB::require(t_id id) const	{ return AbstractDB::require(id); }
