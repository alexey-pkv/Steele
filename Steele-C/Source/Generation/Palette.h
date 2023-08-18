#ifndef STEELE_PALETTE_H
#define STEELE_PALETTE_H


#include "Generation/Palette/GenericPalettes.h"


namespace Steele
{
	class Palette
	{
	private:
		t_id 			id;
		
		GroundPalette	m_ground;
		
		
	public:
		inline const GroundPalette& Ground() const { return m_ground; }
	};
}


#endif