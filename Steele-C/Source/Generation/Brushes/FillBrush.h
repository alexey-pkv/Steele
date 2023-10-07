#ifndef STEELE_FILLBRUSH_H
#define STEELE_FILLBRUSH_H


#include "Base/Generation/IBrush.h"
#include "Generation/BrushSettings/Direction/DirectionSettings.h"
#include "DataTypes/IDMap.h"


namespace Steele
{
	class FillBrush : public AbstractBrush<BrushType::Fill>
	{
	private:
		DirectionSettings	m_dir		= DirectionSettings();
		t_id				m_groundID	= NULL_ID;
		t_id				m_paletteID	= NULL_ID;
		
	
	public:
		~FillBrush() override = default;
		
		
	public: // AbstractBrush
		bool can_fill(const Area& a) const override;
		void paint(IGenerationScope& scope, const Area& area) const override;
		
		
	public: 
		inline DirectionSettings& direction_settings() { return m_dir; }
		inline const DirectionSettings& get_direction_settings() const { return m_dir; }
		inline void set_direction_settings(const DirectionSettings& s) { m_dir = s; }
		
		inline t_id get_ground_id() const { return m_groundID; }
		inline void set_ground_id(t_id id) { m_groundID = id; m_paletteID = NULL_ID; }

		inline t_id get_palette_id() const { return m_paletteID; }
		inline void set_palette_id(t_id id) { m_paletteID = id; m_groundID = NULL_ID; }
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const override;
		void json_read(const nlohmann::json& from) override;
	};
}


#endif