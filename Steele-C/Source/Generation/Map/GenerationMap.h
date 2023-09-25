#ifndef STEELE_GENERATIONMAP_H
#define STEELE_GENERATIONMAP_H


#include "AbstractGenerationMap.h"


namespace Steele
{
	class GenerationMap : public AbstractGenerationMap<Cell>
	{
	public:
		std::string debug_info() const override;
	};
}


#endif