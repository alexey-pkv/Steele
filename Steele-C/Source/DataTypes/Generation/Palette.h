#ifndef STEELE_PALETTE_H
#define STEELE_PALETTE_H


#include "DataTypes/Generation/Palette/GenericPalettes.h"
#include "DataTypes/Generation/Palette/BrushPalette.h"


namespace Steele
{
	class Palette
	{
	private:
		t_id m_id = NULL_ID;
		
		GenericIDPalette m_ground;
		GenericIDPalette m_brushes;
		
		
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
		inline const GenericIDPalette& ground() const { return m_ground; }
		inline const GenericIDPalette& brushes() const { return m_brushes; }
		
		inline GenericIDPalette& ground() { return m_ground; }
		inline GenericIDPalette& brushes() { return m_brushes; }
	};
}


#endif