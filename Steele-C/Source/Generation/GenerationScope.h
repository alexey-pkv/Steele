#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Base/Generation/IGenerationScope.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Map/GenerationMap.h"

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
		RNG::XoroshiroRNG		m_rng;
		GenerationMap			m_map;
		::map<t_id, Palette>	m_pallets = {};	
		
		
	public:
		GenerationScope();
		~GenerationScope() = default;
		
		
	public:
		RNG::IRNG& rng() override;
		IGenerationWorldMap& map() override;
		const IGenerationWorldMap& map() const override;
		
		Palette* get_pallet(t_id id) override;
		const Palette* get_pallet(t_id id) const override;
		bool has_pallet(t_id id) const override;
	
	
	public:
		inline void add_pallet(Palette& p) { m_pallets[p.get_id()] = p; }
		inline void add_pallet(Palette* p) { m_pallets[p->get_id()] = *p; }
	};
}


#endif