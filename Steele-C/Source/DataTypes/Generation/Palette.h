#ifndef STEELE_PALETTE_H
#define STEELE_PALETTE_H


#include "DataTypes/Generation/Palette/Palettes.h"
#include "DataTypes/Generation/Palette/BrushPalette.h"


namespace Steele
{
	class Palette
	{
	private:
		t_id m_id = STEELE_NULL_ID;
		
		GenericIDPalette	m_ground;
		BrushPalette		m_brushes;
		
		
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
		inline GenericIDPalette& ground() { return m_ground; }
		inline const GenericIDPalette& ground() const { return m_ground; }
		
		inline BrushPalette& brushes() { return m_brushes; }
		inline const BrushPalette& brushes() const { return m_brushes; }
	};
}


#endif
