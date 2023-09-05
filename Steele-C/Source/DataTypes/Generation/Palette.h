#ifndef STEELE_PALETTE_H
#define STEELE_PALETTE_H


#include "DataTypes/Generation/Palette/GenericPalettes.h"
// #include "Generation/Palette/TemplatesPalette.h"


namespace Steele
{
	class Palette
	{
	private:
		t_id 			m_id;
		
		GroundPalette		m_ground;
		// TemplatesPalette	m_templates;
		
		
	public:
		~Palette() = default;
		
		Palette() = default;
		Palette(const Palette&) = default;
		Palette(Palette&&) = default;
		
		Palette& operator=(const Palette&) = default;
		Palette& operator=(Palette&&) = default;
		
		
	public:
		inline t_id get_id() const { return m_id; }
		void set_id(t_id id) { m_id = id; }
		
		
	public:
		inline const GroundPalette& ground() const { return m_ground; }
		// inline const TemplatesPalette& Templates() const { return m_templates; }
	};
}


#endif