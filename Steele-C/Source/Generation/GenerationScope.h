#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Base/Generation/IGenerationScope.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Map/GenerationMap.h"


namespace Steele
{
	class GenerationScope : public IGenerationScope
	{
	public:
		GenerationScope(GenerationScope&&) = delete;
		GenerationScope(const GenerationScope&) = delete;
		
		
	private:
		RNG::XoroshiroRNG	m_rng;
		GenerationMap		m_map;
		
		
	public:
		GenerationScope();
		~GenerationScope() = default;
		
		
	public:
		RNG::IRNG& rng() override;
		IGenerationWorldMap& map() override;
		const IGenerationWorldMap& map() const override;
		
	};
}


#endif