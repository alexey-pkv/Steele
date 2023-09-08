#ifndef STEELE_AREABRUSH_H
#define STEELE_AREABRUSH_H


#include "DataTypes/Area.h"
#include "Generation/Brushes/AreaBrush/AreaComponent.h"
#include "Base/Generation/IBrush.h"

#include <string>
#include <vector>


namespace Steele
{
	class AreaBrush : public AbstractBrush<BrushType::Area>
	{
	private:
		std::vector<AreaComponent>	m_components = {};
		
		
	public:
		~AreaBrush() override = default;
		AreaBrush() = default;
		
		
	public:
		bool is_valid() const;
		
		Area total_area() const;
		
		void remove_at(int index);
		void remove_at(int from, int to);
		void add_area(const Area& a);
		void add_area(const Area& a, const string& name);
		void move(int from, int to);
		
		
	public:
		inline size_t size() { return m_components.size(); }
		inline std::vector<AreaComponent>::const_iterator being() const { return m_components.cbegin(); }
		inline std::vector<AreaComponent>::const_iterator end() const { return m_components.cend(); }
		
		
	public: // IBrush
		void paint(IGenerationScope& scope, const Area& area) const override;
	};
}


#endif