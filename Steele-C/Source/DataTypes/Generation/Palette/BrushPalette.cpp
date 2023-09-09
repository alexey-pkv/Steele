#include "BrushPalette.h"


#include "Base/Generation/IGenerationScope.h"


const Steele::IBrush* Steele::BrushPalette::select_random(Steele::IGenerationScope& scope, const Steele::Area& a) const
{
	GenericIDPalette curr;
	auto& db = scope.brush_db();
	
	for (auto [id, w] : this->palette())
	{
		auto brush = db.get(id);
		
		if (!brush || !brush->can_fill(a))
			continue;
		
		curr.add(id, w);
	}
	
	if (curr.is_empty())
		throw PaintException("No brushes found to fill area");
	
	auto id = curr.select_random(scope.rng());
	
	return db.get(id);
}
