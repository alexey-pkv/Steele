#ifndef STEELE_PALETTE_H
#define STEELE_PALETTE_H


#include "DataTypes/Generation/Palette/GenericPalettes.h"
// #include "Generation/Palette/TemplatesPalette.h"


namespace Steele
{
	class Palette
	{
	private:
		t_id 			id;
		
		GroundPalette		m_ground;
		// TemplatesPalette	m_templates;
		
		
	public:
		inline const GroundPalette& Ground() const { return m_ground; }
		// inline const TemplatesPalette& Templates() const { return m_templates; }
	};
}


#endif