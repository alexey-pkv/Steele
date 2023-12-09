#ifndef STEELE_GENERATIONRESOURCESDB_H
#define STEELE_GENERATIONRESOURCESDB_H


#include "Palette.h"

#include "Base/Generation/IBrush.h"
#include "Base/Generation/DB/ResourcesDB.h"


namespace Steele
{
	class GenerationResourcesDB
	{
	private:
		ResourcesDB<IBrush>		m_brushes;
		ResourcesDB<Palette>	m_palettes;
		
		
	public:
		GenerationResourcesDB() = default;
		~GenerationResourcesDB() = default;
		
		
	public:
		inline ResourcesDB<IBrush>& brushes() { return m_brushes; }
		inline ResourcesDB<Palette>& palettes() { return m_palettes; }
		
		inline const ResourcesDB<IBrush>& brushes() const { return m_brushes; }
		inline const ResourcesDB<Palette>& palettes() const { return m_palettes; }
		
		
	public:
		int count() const;
		void clear();
		bool remove(t_id id);
		bool has(t_id id) const;
	};
	
	class ResourceLink
	{
	private:
		t_id						m_id	= STEELE_NULL_ID;
		wptr<GenerationResourcesDB>	m_db;
		
		
	public:
		ResourceLink() = default;
		~ResourceLink();
		
		
	public:
		void set(t_id id, const sptr<GenerationResourcesDB>& db);
		bool remove();
		void clear();
	};
}


#endif