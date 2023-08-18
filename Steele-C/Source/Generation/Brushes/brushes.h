#ifndef STEELE_BRUSHES_H
#define STEELE_BRUSHES_H


#include "DataTypes/Area.h"

#include "Generation/IGenerationScope.h"
#include "Generation/Brushes/Settings/FillSettings.h"


namespace Steele
{
	void fill(IGenerationScope& gs, const Area& a, const FillSettings& fs);
}

#endif