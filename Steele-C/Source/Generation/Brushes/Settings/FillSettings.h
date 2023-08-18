#ifndef STEELE_FILLSETTINGS_H
#define STEELE_FILLSETTINGS_H


#include "DataTypes/Types.h"
#include "DirectionSettings.h"

#include <string>


namespace Steele
{
	struct FillSettings
	{
	private:
		DirectionSettings	m_dir		= DirectionSettings();
		t_id				m_groundID	= NULL_ID;
		t_id				m_paletteID	= NULL_ID;
		
		
	public:
		inline const DirectionSettings& Direction() const { return m_dir; }
		inline t_id GetGroundID() const { return m_groundID; }
		inline t_id GetPaletteID() const { return m_paletteID; }
		
		
	public:
		void SetGroundID(t_id id);
		void SetPaletteID(t_id id);
	};
}


#endif