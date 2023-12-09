#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Base/Generation/IGenerationScope.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Map/GenerationMap.h"
#include "Base/Map/AbortMap.h"

#include <map>


using namespace std;


namespace Steele
{
	class GenerationScope : public IGenerationScope
	{
	public:
		GenerationScope(GenerationScope&&) = delete;
		GenerationScope(const GenerationScope&) = delete;
		
		
	private:
		sptr<const GenerationResourcesDB> m_db = nullptr;
		
		XoroshiroRNG	m_rng;
		
		AbortMap<Cell>	m_abort;
		
		sptr<IMap<Cell>>	m_target	= nullptr;
		uptr<GenerationMap>	m_map 		= nullptr;
		
		uint64_t m_targetSize = 0;
		
		
	public:
		virtual ~GenerationScope() = default;
		GenerationScope() = default;
		
		
	public:
		IRNG& rng() override;
		IStateRNG& rng_state() override;
		const IStateRNG& rng_state() const override;
		IGenerationWorldMap& map() override;
		const IGenerationWorldMap& map() const override;
		const GenerationResourcesDB& db() const override;
		
		void set_rng_state(const RandomState& state) override;
		void using_map(sptr<IMap<Cell>> map) override;
		void using_db(sptr<const GenerationResourcesDB> db) override;
		void validate_abort() override;
		double get_progress() const override;
		void abort() override;
		
		bool generate() override;
		bool generate(const IBrush& brush, const Area& area) override;
		
		void reset_generation() override;
		
	
	public:
		
	};
}


#endif