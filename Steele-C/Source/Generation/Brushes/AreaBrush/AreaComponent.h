#ifndef STEELE_AREACOMPONENT_H
#define STEELE_AREACOMPONENT_H


#include <utility>

#include "DataTypes/Area.h"
#include "Base/Generation/IBrush.h"


namespace Steele
{
	class AreaComponent : public AbstractBrush<BrushType::AreaComponent>
	{
	private:
		Area		m_area;
		Direction	m_direction	= Direction::North;
		bool 		m_isLocal	= false;
		t_id		m_brushID	= NULL_ID;
		t_id 		m_paletteID	= NULL_ID;
		
		
	public:
		~AreaComponent() override = default;
		AreaComponent() = default;
		
		explicit AreaComponent(Area area);
		explicit AreaComponent(Area area, string name);
		
		
	public: // IBrush
		void paint(IGenerationScope& scope, const Area& area) const override;
		
		
	public:
		inline bool is_local() const { return m_isLocal; }
		inline void set_local() { m_isLocal = true; }
		inline void set_local(bool isLocal) { m_isLocal = isLocal; }
		inline void set_shared() { m_isLocal = false; }
		
		inline Area& area() { return m_area; }
		inline const Area& area() const { return m_area; }
		
		inline uint64_t area_size() const { return m_area.get_area(); }
		
		inline Direction get_direction() const { return m_direction; }
		inline void set_direction(Direction d) { m_direction = d; }
		
		inline t_id get_brush_id() const { return m_brushID; }
		inline void set_brush_id(t_id id) { m_brushID = id; m_paletteID = NULL_ID; }
		inline bool has_brush_id() const { return m_brushID != NULL_ID; }
		
		inline t_id get_palette_id() const { return m_paletteID; }
		inline void set_palette_id(t_id id) { m_paletteID = id; m_brushID = NULL_ID; }
		inline bool has_palette_id() const { return m_brushID != NULL_ID; }
		
		
	public:
		void paint_in_area(IGenerationScope& scope) const;
	};
}


#endif