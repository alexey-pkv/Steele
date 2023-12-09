#include "GenerationMap.h"

#include <utility>


using namespace Steele;


GenerationMap::GenerationMap(sptr<IMap<Cell>> map) : AbstractGenerationMap<Cell>(std::move(map))
{
	
}
