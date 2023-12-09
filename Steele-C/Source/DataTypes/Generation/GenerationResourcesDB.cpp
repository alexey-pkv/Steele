#include "GenerationResourcesDB.h"


using namespace Steele;


int GenerationResourcesDB::count() const
{
	return 
		m_brushes.count() + 
		m_palettes.count();
}

void GenerationResourcesDB::clear()
{
	m_palettes.clear();
	m_brushes.clear();
}

bool GenerationResourcesDB::remove(t_id id)
{
	return 
		m_brushes.remove(id) || 
		m_palettes.remove(id);
}

bool GenerationResourcesDB::has(t_id id) const
{
	return 
		m_brushes.has(id) || 
		m_palettes.has(id);
}


ResourceLink::~ResourceLink()
{
	remove();
}

bool ResourceLink::remove()
{
	if (m_id == STEELE_NULL_ID)
		return false;
	
	auto db = m_db.lock();
		
	if (db)
	{
		db->remove(this->m_id);
	}
		
	clear();
	
	return true;
}

void ResourceLink::set(t_id id, const sptr<GenerationResourcesDB>& db)
{
	remove();
	
	m_id = id;
	m_db = db;
}

void ResourceLink::clear()
{
	m_id = STEELE_NULL_ID;
	m_db.reset();
}
