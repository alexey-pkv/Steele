#ifndef STEELE_LOCALTRANSFORMATION_H
#define STEELE_LOCALTRANSFORMATION_H


#include "DataTypes/Transformation.h"


namespace Steele
{
	class ITransformable;
	
	
	class LocalTransformation
	{
	private:
		ITransformable* m_source;
		Transformation	m_t = Transformation::ZERO;
		bool			m_isApplied;
		
		
	public:
		inline void set_transformation(Direction dir) { set_transformation(Transformation { dir }); };
		inline void set_transformation(const v2i& t, Direction dir = Direction::North) { set_transformation(Transformation { { t.x, t.y, 0 }, dir }); };
		inline void set_transformation(const v2i& t, int z, Direction dir = Direction::North) { set_transformation(Transformation { { t.x, t.y, z }, dir }); };
		inline void set_transformation(const v3i& t, Direction dir = Direction::North) { set_transformation(Transformation(t, dir)); };
		
		inline void add_transformation(Direction dir) { add_transformation(Transformation(dir)); };
		inline void add_transformation(const v2i& t, Direction dir = Direction::North) { add_transformation(Transformation { { t.x, t.y, 0 }, dir }); };
		inline void add_transformation(const v2i& t, int z, Direction dir = Direction::North) { add_transformation(Transformation { { t.x, t.y, z }, dir }); };
		inline void add_transformation(const v3i& t, Direction dir = Direction::North) { add_transformation(Transformation { t, dir }); };
		inline void add_transformation(const Transformation& t) { set_transformation(m_t + t); }
		
		inline bool is_transformed() const { return m_isApplied; }
		inline const Transformation& transformation() const { return m_t; }
		
		
	public:
		void set_transformation(const Transformation& t);
		
		
	public:
		~LocalTransformation();
		LocalTransformation(LocalTransformation&& source) noexcept;
		LocalTransformation(ITransformable* parent);
		LocalTransformation(ITransformable& parent);
		LocalTransformation(ITransformable* parent, const Transformation& t);
		LocalTransformation(ITransformable& parent, const Transformation& t);
	
	
	public:
		void reset_transformation();
	};
}


#endif