#ifndef STEELE_ITRANSFORMABLE_H
#define STEELE_ITRANSFORMABLE_H


#include "TransformationStack.h"
#include "Exceptions/MapExceptions.h"

#include "DataTypes/Types.h"
#include "DataTypes/Transformation.h"


namespace Steele
{
	class ITransformable
	{
	protected:
		virtual void _push_transformation(const Transformation& t) = 0;
		
		
	public:
		inline void push_transformation(const v2i& t, Direction dir = Direction::North) { _push_transformation({ .Dir = dir, .Offset = { t.x, t.y, 0 } }); };
		inline void push_transformation(const v2i& t, int z, Direction dir = Direction::North) { _push_transformation({ .Dir = dir, .Offset = { t.x, t.y, z } }); };
		inline void push_transformation(const v3i& t, Direction dir = Direction::North) { _push_transformation({ .Dir = dir, .Offset = t }); };
		inline void push_transformation(const Transformation& t) { _push_transformation(t); };
		
		
	public:
		virtual void pop_transformation() = 0;
		virtual void reset_transformation() = 0;
		virtual bool is_transformed() const = 0;
		virtual Transformation peek_transformation() const = 0;
		virtual const Transformation& transformation() const = 0;
	};
	
	
	class LocalTransformation : public ITransformable
	{
	private:
		ITransformable* m_source;
		bool			m_isApplied;
		
		
	protected: // ITransformable
		void _push_transformation(const Transformation& t) override;
		
		
	public:
		~LocalTransformation();
		LocalTransformation(ITransformable* parent);
		LocalTransformation(ITransformable& parent);
	
	
	public: // ITransformable
		void pop_transformation() override;
		void reset_transformation() override;
		bool is_transformed() const override;
		Transformation peek_transformation() const override;
		const Transformation& transformation() const override;
	};
	
	
	class AbstractTransformable : public ITransformable
	{
	private:
		TransformationStack m_stack		= TransformationStack();
		
		
	protected:
		inline const TransformationStack& transformation_stack() const { return m_stack; }
		
		
	protected:
		void _push_transformation(const Transformation& t) override;
		
		
	public:
		void pop_transformation() override;
		void reset_transformation() override;
		bool is_transformed() const override;
		Transformation peek_transformation() const override;
		const Transformation& transformation() const override;
	};
}


#define PUSH_TRANSFORM(map, offset, dir) \
	LocalTransformation __lt__(map); \
	__lt__.push_transformation(offset, dir)
	
#define PUSH_TRANSFORM_V(map, offset) \
	PUSH_TRANSFORM(map, offset, Steele::Direction::North)
	
#define PUSH_TRANSFORM_DIR(map, dir) \
	PUSH_TRANSFORM(map, v2i_zero, dir)


#endif