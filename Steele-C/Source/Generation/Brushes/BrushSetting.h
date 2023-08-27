#ifndef STEELE_BRUSHSETTING_H
#define STEELE_BRUSHSETTING_H


#include <string>

#include "DataTypes/Types.h"
#include "FillSettings.h"
#include "CanvasTemplate.h"
#include "TemplateBrush.h"


namespace Steele
{
	struct BrushSetting
	{
	public:
		std::string Name;
		BrushType	Type;
		
		union
		{
			FillSettings	Fill;
			CanvasTemplate	Canvas;
			TemplateBrush	Template;
		}
		Setting;
	};
}


#endif