#ifndef STEELE_IBRUSH_H
#define STEELE_IBRUSH_H


#include "IGenerationScope.h"
#include "DataTypes/Area.h"
#include "Exceptions/PaintException.h"


namespace Steele
{
	class IBrush
	{
	public:
		virtual BrushType get_brush_type() const noexcept = 0;
		virtual void paint(IGenerationScope& scope, const Area& area) const = 0;
		virtual bool try_paint(IGenerationScope& scope, const Area& area) const noexcept = 0;
	};
	
	template <BrushType B>
	class AbstractBrush : public IBrush
	{
	public:
		bool try_paint(IGenerationScope& scope, const Area& area) const noexcept override
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
		
		BrushType get_brush_type() const noexcept override
		{
			return B;
		}
	};
}


#endif