#ifndef STEELE_MAP_DEBUG_H
#define STEELE_MAP_DEBUG_H


#include <string>

#include "DataTypes/Map/Cell.h"
#include "Base/Map/SimpleMap.h"


namespace Steele
{
	std::string debug_info(const SimpleMap<Cell>& source);
}


#endif
