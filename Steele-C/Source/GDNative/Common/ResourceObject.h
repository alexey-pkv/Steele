#ifndef STEELE_RESOURCEOBJECT_H
#define STEELE_RESOURCEOBJECT_H


#include "DataTypes/Generation/GenerationResourcesDB.h"


namespace godot
{
	class ResourceObject
	{
	private:
		Steele::ResourceLink m_link;
		
		
	public:
		inline Steele::ResourceLink& link() { return m_link; }
	};
}


#endif