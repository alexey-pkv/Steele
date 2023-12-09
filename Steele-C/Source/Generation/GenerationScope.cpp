#include "GenerationScope.h"


using namespace Steele;


IStateRNG& 					GenerationScope::rng_state()		{ return m_rng; }
const IStateRNG&			GenerationScope::rng_state() const	{ return m_rng; }
IGenerationWorldMap&		GenerationScope::map() 				{ return *m_map; }
const IGenerationWorldMap&	GenerationScope::map() const		{ return *m_map; }
const GenerationResourcesDB& GenerationScope::db() const		{ return *m_db; }


IRNG& GenerationScope::rng() 
{
	validate_abort();
	return m_rng;
}


void GenerationScope::set_rng_state(const RandomState& state)
{
	m_rng.set_state(state);
}

void GenerationScope::using_map(sptr<IMap<Cell>> map)
{
	m_target = map;
}

void GenerationScope::using_db(sptr<const GenerationResourcesDB> db)
{
	m_db = db;
}

void GenerationScope::validate_abort()
{
	m_abort.validate_abort();
}

double GenerationScope::get_progress() const
{
	if (!m_map)
		return 0;
	
	auto size = (double)m_map->size();
	auto target = (double)m_targetSize;
	
	return size / target;
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


bool GenerationScope::generate(const IBrush& brush, const Area& area)
{
	if (!m_target)
		return false;
	
	m_targetSize = area.get_area();
	m_target->clear();
	m_map = make_unique<GenerationMap>(m_target);
	
	try
	{
		brush.paint(*this, area);
	}
	catch (const AbortException& e)
	{
		// Do nothing, abort was requested.
	}
	
	m_map.reset();
	
	return false;
}
