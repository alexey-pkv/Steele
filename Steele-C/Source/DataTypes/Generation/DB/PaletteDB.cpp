#include "PaletteDB.h"


Steele::Palette* Steele::PaletteDB::create(t_id id)
{
	auto* p = IPaletteDB::create(id);
	
	p->set_id(id);
	
	return p;
}
