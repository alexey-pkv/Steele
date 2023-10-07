#ifndef STEELE_IBRUSHDB_H
#define STEELE_IBRUSHDB_H


#include "Base/Generation/IBrush.h"
#include "Generation/Brushes/FillBrush.h"
#include "Generation/Brushes/CanvasBrush.h"
#include "Generation/Brushes/AreaBrush.h"
#include "Generation/Brushes/RowBrush.h"
#include "IAbstractDB.h"


namespace Steele
{
	class IBrushDB : public IAbstractDB<IBrush>
	{
	public:
		virtual IBrush* create(t_id id, BrushType type) = 0;
		virtual FillBrush* create_fill(t_id id) = 0;
		virtual CanvasBrush* create_canvas(t_id id) = 0;
		virtual AreaBrush* create_area(t_id id) = 0;
		virtual RowBrush* create_row(t_id id) = 0;
		
		
	public:
		inline IBrush* create_from_json(t_id id, BrushType type, const json& json)
		{
			auto b = create(id, type);
			b->json_read(json);
			return b;
		}
	};
}


#endif