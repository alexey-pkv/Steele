#include "GenerationScope.h"


using namespace Steele;


IRNG& 						GenerationScope::rng()				{ return m_rng;}
IStateRNG& 					GenerationScope::rng_state()		{ return m_rng; }
const IStateRNG&			GenerationScope::rng_state() const	{ return m_rng; }
IGenerationWorldMap&		GenerationScope::map() 				{ return m_map; }
const IGenerationWorldMap&	GenerationScope::map() const		{ return m_map; }
IPaletteDB&					GenerationScope::palette_db()		{ return m_pallets; }
IBrushDB&					GenerationScope::brush_db()			{ return m_brushes; }


