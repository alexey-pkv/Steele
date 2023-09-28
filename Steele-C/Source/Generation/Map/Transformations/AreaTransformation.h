#ifndef STEELE_AREATRANSFORMATION_H
#define STEELE_AREATRANSFORMATION_H


#include "DataTypes/Transformation.h"
#include "DataTypes/Area.h"


namespace Steele
{
	class ITransformable;
	
	
	class AreaTransformation
	{
	private:
		ITransformable* m_source;
		Area*			m_area;
		
		v2i				m_offset	= v2i_zero;
		Direction		m_dir		= Direction::North;
		bool			m_isApplied	= false;
		
		
	public:
		inline void set_transformation(Direction dir) { set_transformation(v2i_zero, dir); };
		inline void add_transformation(Direction dir) { if (dir != Direction::North) set_transformation(m_offset, m_dir + dir); };
		inline void add_transformation(const v2i& v, Direction dir = Direction::North) { set_transformation(m_offset + v, m_dir + dir); };
		inline void align_to_area() { add_transformation(m_area->offset()); }
		
		
		inline bool is_transformed() const { return m_isApplied; }
		inline v2i offset() const { return m_offset; }
		inline Direction direction() const { return m_dir; }
		inline Transformation transformation() const { return { .Dir = m_dir, .Offset = { m_offset.x, m_offset.y, 0 } }; }
		
		
	public:
		void set_transformation(const v2i& v, Direction dir);
		
	
	public:
		~AreaTransformation();
		AreaTransformation(AreaTransformation&& source) noexcept;
		AreaTransformation(ITransformable* parent, Area* area);
		AreaTransformation(ITransformable* parent, Area* area, v2i v, Direction dir);
	
	
	public:
		void reset_transformation();
	};
}


#endif