#ifndef STEELE_IBRUSH_H
#define STEELE_IBRUSH_H


#include "IGenerationScope.h"
#include "DataTypes/Area.h"


namespace Steele
{
	class IBrush
	{
	public:
		virtual void paint(IGenerationScope& scope, const Area& area) const = 0;
		virtual bool try_paint(IGenerationScope& scope, const Area& area) const noexcept = 0;
	};
	
	class AbstractBrush : public IBrush
	{
	public:
		bool try_paint(IGenerationScope& scope, const Area& area) const noexcept override;
	};
}


#endif