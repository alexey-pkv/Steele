#ifndef STEELE_CANVASBRUSH_H
#define STEELE_CANVASBRUSH_H


#include "Base/Generation/IBrush.h"
#include "Base/Map/SimpleMap.h"
#include "DataTypes/Map/Cell.h"


namespace Steele
{
	class CanvasBrush : public AbstractBrush<BrushType::Canvas>
	{
	private:
		SimpleMap<Cell>	m_canvas = {};
		
		
	public:
		CanvasBrush() = default;
		CanvasBrush(const CanvasBrush&) = default;
		CanvasBrush(CanvasBrush&&) = default;
		
		~CanvasBrush() override = default;
		
		
	public: // AbstractBrush
		bool can_fill(const Area& a) const override;
		void paint(IGenerationScope& scope, const Area& area) const override;
		
		bool is_constant_area_brush() const override;
		
		Area get_constant_area() const override;
	
	
	public:
		inline SimpleMap<Cell>& canvas() { return m_canvas; }
		inline const SimpleMap<Cell>& canvas() const { return m_canvas; }
		
		
	public:
		void debug_set(const Area& a, t_id id);
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const override;
		void json_read(const nlohmann::json& from) override;
	};
}


#endif