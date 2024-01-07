#ifndef STEELE_LOCATION_H
#define STEELE_LOCATION_H


#include "DataTypes/Types.h"
#include "Utils.h"
#include "DataTypes/Area.h"
#include "Element.h"


namespace Steele
{
	struct Location : public Element
	{
	public:
		Area		LocationArea	= Area::ZERO;
		int 		Floor			= 0;
		bool 		IsActive		= false;
		vec<v3i>	Regions			= {};
	};
}


#endif