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
		virtual string name() const = 0;
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
	private:
		string m_name;
		
		
	public:
		AbstractBrush() = default;
		
		
	public:
		void set_name(const string& name) { m_name = name; }
		void set_name(string&& name) { m_name = std::move(name); }
		
		
	public: // IBrush
		string name() const override
		{
			return m_name;
		}
		
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