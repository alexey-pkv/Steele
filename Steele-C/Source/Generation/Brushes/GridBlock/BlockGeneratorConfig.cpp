#include "BlockGeneratorConfig.h"
#include "Exceptions/SteeleException.h"


int Steele::BlockGeneratorConfig::total_weight() const
{
	int w = 0;
	
	for (auto& b : Blocks)
	{
		w += b.Weight;
	}
	
	return w;
}
