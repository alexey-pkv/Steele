#ifndef STEELE_AREATEMPLATE_H
#define STEELE_AREATEMPLATE_H


#include "CanvasTemplate.h"
#include "DataTypes/Area.h"

#include <string>
#include <vector>


namespace Steele
{
	class AreaTemplate
	{
	public:
		struct Placement
		{
			std::string SettingsName;
			Area		PlacementArea;
		};
		
		
	public:
		CanvasTemplate			Canvas;
		std::vector<Placement>	Components;
	};
}


#endif