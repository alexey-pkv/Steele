#ifndef STEELE_PALETTEDB_H
#define STEELE_PALETTEDB_H


#include "Base/Generation/DB/IPatetteDB.h"


namespace Steele
{
	class PaletteDB : public IPaletteDB
	{
	public:
		Palette* create(t_id id) override;
	};
}


#endif
