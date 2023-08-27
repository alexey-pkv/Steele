#ifndef STEELE_CANVASTEMPLATE_H
#define STEELE_CANVASTEMPLATE_H


#include <map>
#include "DataTypes/Types.h"
#include "FillSettings.h"


namespace Steele
{
	using namespace std;
	
	
	struct CanvasTemplate
	{
	public:
		map<v2i, FillSettings> Canvas;
	};
}


#endif