#ifndef STEELE_BRUSHDB_H
#define STEELE_BRUSHDB_H


#include <map>

#include "Utils.h"

#include "Base/Generation/DB/IBrushDB.h"


namespace Steele
{
	class BrushDB : public IBrushDB, public AbstractDB<IBrush>
	{
	public: // AbstractDB
		bool has(t_id id) override;
		IBrush* get(t_id id) override;
		const IBrush* get(t_id id) const override;
		bool remove(t_id id) override;
		
		IBrush* require(t_id id) override;
		
		const IBrush* require(t_id id) const override;
	
	
	public:	// IBrushDB
		IBrush* create(t_id id, BrushType type) override;
		FillBrush* create_fill(t_id id) override;
		CanvasBrush* create_canvas(t_id id) override;
		AreaBrush* create_area(t_id id) override;
	};
}


#endif