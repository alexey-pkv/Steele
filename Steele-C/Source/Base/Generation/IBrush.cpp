#include "IBrush.h"
#include "Exceptions/PaintException.h"


bool Steele::AbstractBrush::try_paint(Steele::IGenerationScope& scope, const Steele::Area& area) const noexcept
{
	try
	{
		paint(scope, area);
	}
	catch (const PaintException&)
	{
		return false;
	}
	
	return true;
}
