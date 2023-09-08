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
		virtual string name() const = 0;
		virtual BrushType get_brush_type() const noexcept = 0;
		virtual void paint(IGenerationScope& scope, const Area& area) const = 0;
		virtual bool try_paint(IGenerationScope& scope, const Area& area) const noexcept = 0;
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
		
		BrushType get_brush_type() const noexcept override
		{
			return B;
		}
	};
}


#endif