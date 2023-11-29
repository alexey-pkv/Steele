#include "GenerationScope.h"


using namespace Steele;


IRNG& 						GenerationScope::rng()				{ return m_rng;}
IStateRNG& 					GenerationScope::rng_state()		{ return m_rng; }
const IStateRNG&			GenerationScope::rng_state() const	{ return m_rng; }
IGenerationWorldMap&		GenerationScope::map() 				{ return *m_map; }
const IGenerationWorldMap&	GenerationScope::map() const		{ return *m_map; }
IPaletteDB&					GenerationScope::palette_db()		{ return m_pallets; }
IBrushDB&					GenerationScope::brush_db()			{ return m_brushes; }


void GenerationScope::set_rng_state(const RandomState& state)
{
	m_rng.set_state(state);
}

void GenerationScope::using_map(IMap<Cell>* map)
{
	m_target = map;
}

void GenerationScope::validate_abort()
{
	m_abort.validate_abort();
}

float GenerationScope::get_progress() const
{
	return 1;
}

void GenerationScope::abort()
{
	m_abort.abort();
}

bool GenerationScope::generate()
{
	if (!m_target)
		return false;
	
	m_map = make_unique<GenerationMap>(m_target);
	
	return false;
}

void GenerationScope::reset_generation()
{
	m_abort.reset_abort();
}


bool GenerationScope::generate(IBrush& brush, const Area& area)
{
	if (!m_target)
		return false;
	
	m_target->clear();
	m_map = make_unique<GenerationMap>(m_target);
	
	brush.paint(*this, area);
	
	m_map.reset();
	
	return false;
}
