#ifndef STEELE_ALIGNSETTINGS_H
#define STEELE_ALIGNSETTINGS_H


#include "DataTypes/Types.h"
#include "outline_scalar_iterator.h"


namespace Steele::Align
{
	struct AlignSettings
	{
	public:
		enum Style
		{
			Overlap,
			Touch
		};
	public:
		const Area&	Source;
		const Area& Target;
		
		outline_scalar_iterator_provider SourceIterator;
		outline_scalar_iterator_provider TargetIterator;
		
		Style		Positioning;
		Direction	AlignmentDirection;
		v2i 		AlignmentVector;
		
		bool 		AllowGap;
	};
}


#endif