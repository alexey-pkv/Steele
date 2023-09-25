#include "GenerationMap.h"
#include "RNG/XoroshiroRNG.h"


#include "Debug/MapDebug.h"


std::string Steele::GenerationMap::debug_info() const
{
	return std::move(Steele::debug_info(map()));
}
