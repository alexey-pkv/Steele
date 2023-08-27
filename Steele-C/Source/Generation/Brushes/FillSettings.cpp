#include "FillSettings.h"


void Steele::FillSettings::SetGroundID(t_id id)
{
	if (id != NULL_ID)
	{
		m_paletteID = NULL_ID;
	}
	
	m_groundID = id;
}

void Steele::FillSettings::SetPaletteID(t_id id)
{
	if (id != NULL_ID)
	{
		m_groundID = NULL_ID;
	}
	
	m_paletteID = id;
}
