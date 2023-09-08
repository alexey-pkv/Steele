#include "CanvasBrush.h"


#include "Base/Generation/IGenerationScope.h"


void Steele::CanvasBrush::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	auto& map = scope.map();
	
	for (const auto& kvp : m_canvas)
	{
		v2i pos = { kvp.first.x, kvp.first.y };
		
		if (!area.contains(pos))
			throw CanvasAreaOutsideOfBoundException(pos);
		
		map.set(kvp.second, pos);
	}
}
