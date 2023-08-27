#ifndef STEELE_TEMPLATEBRUSH_H
#define STEELE_TEMPLATEBRUSH_H


#include "CanvasTemplate.h"
#include "DataTypes/Area.h"

#include <string>
#include <vector>


namespace Steele
{
	class TemplateBrush
	{
	public:
		struct Placement
		{
			std::string SettingsName;
			Area		PlacementArea;
		};
		
		
	public:
		std::string 			Name;
		Steele::Area			Area;
		CanvasTemplate			Canvas;
		std::vector<Placement>	Components;
		
		
	public:
		TemplateBrush(const TemplateBrush& brush) = default;
		TemplateBrush(TemplateBrush&& brush) = default;
		TemplateBrush() = default;
		~TemplateBrush() = default;
	};
}


#endif