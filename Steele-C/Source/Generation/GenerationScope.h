#ifndef STEELE_GENERATIONSCOPE_H
#define STEELE_GENERATIONSCOPE_H


#include "Base/Generation/IGenerationScope.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Map/GenerationMap.h"
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
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
		XoroshiroRNG	m_rng;
		PaletteDB		m_pallets;
		BrushDB			m_brushes;
		
		AbortMap<Cell>	m_abort;
		IMap<Cell>*		m_target	= nullptr;
		
		uptr<GenerationMap>	m_map = nullptr;
		
		
	public:
		virtual ~GenerationScope() = default;
		GenerationScope() = default;
		
		
	public:
		IRNG& rng() override;
		IStateRNG& rng_state() override;
		const IStateRNG& rng_state() const override;
		IGenerationWorldMap& map() override;
		const IGenerationWorldMap& map() const override;
		
		IPaletteDB& palette_db() override;
		IBrushDB& brush_db() override;
		
		void set_rng_state(const RandomState& state) override;
		void using_map(IMap<Cell>* map) override;
		void validate_abort() override;
		float get_progress() const override;
		void abort() override;
		
		bool generate() override;
		bool generate(IBrush& brush, const Area& area) override;
		
		void reset_generation() override;
	};
}


#endif