#ifndef STEELE_IBRUSH_H
#define STEELE_IBRUSH_H


#include "DataTypes/Area.h"
#include "Exceptions/PaintException.h"


namespace Steele
{
	class IGenerationScope;
	
	
	class IBrush
	{
	public:
		virtual ~IBrush() = default;
		
	public:
		virtual bool can_fill(const Area& a) const = 0;
		virtual BrushType get_brush_type() const noexcept = 0;
		virtual void paint(IGenerationScope& scope, const Area& area) const = 0;
		virtual bool try_paint(IGenerationScope& scope, const Area& area) const noexcept = 0;
		virtual bool is_constant_area_brush() const = 0;
		virtual Area get_constant_area() const = 0;
		
		
	public: // JSON
		virtual void json_write(nlohmann::json& into) const = 0;
		virtual void json_read(const nlohmann::json& from) = 0;
	};
	
	template <BrushType B>
	class AbstractBrush : public IBrush
	{
	public:
		AbstractBrush() = default;
		~AbstractBrush() override = default;
		
		
	public: // IBrush
		bool try_paint(IGenerationScope& scope, const Area& area) const noexcept override
		{
			try
			{
				paint(scope, area);
			}
			catch (const PaintException&)
			{
				return false;
			}
			
			return true;
		}
		
		bool is_constant_area_brush() const override
		{
			return false;
		}
		
		Area get_constant_area() const override
		{
			return Area::ZERO;
		}
		
		BrushType get_brush_type() const noexcept override
		{
			return B;
		}
	};
}


#endif