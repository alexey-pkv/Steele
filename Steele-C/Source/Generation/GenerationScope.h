#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Base/Generation/IGenerationScope.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Map/GenerationMap.h"
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"

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
		RNG::XoroshiroRNG	m_rng;
		GenerationMap		m_map;
		PaletteDB			m_pallets;
		BrushDB				m_brushes;
		
		
	public:
		virtual ~GenerationScope() = default;
		GenerationScope();
		
		
	public:
		RNG::IRNG& rng() override;
		IGenerationWorldMap& map() override;
		const IGenerationWorldMap& map() const override;
		
		IPaletteDB& palette_db() override;
		IBrushDB& brush_db() override;
	};
}


#endif