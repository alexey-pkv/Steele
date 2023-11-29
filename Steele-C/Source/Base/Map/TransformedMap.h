#ifndef STEELE_TRANSFORMEDMAP_H
#define STEELE_TRANSFORMEDMAP_H


#include "MapDecorator.h"
#include "DataTypes/Transformation.h"


namespace Steele
{
	template <typename CELL>
	class TransformedMap : public MapDecorator<CELL>
	{
	private:
		Transformation m_transformation;
		
		
	protected:
		CELL* _try_get(v3i at) override
		{
			return this->next().try_get(m_transformation.apply(at));
		}
		
		const CELL* _try_get(v3i at) const override
		{
			return this->next().try_get(m_transformation.apply(at));
		}
		
		CELL* _get(v3i at) override
		{
			return this->next().get(m_transformation.apply(at));
		}
		
		bool _is_empty(v3i at) const override
		{
			return this->next().is_empty(m_transformation.apply(at));
		}
		
		bool _remove(v3i at) override
		{
			return this->next().remove(m_transformation.apply(at));
		}
		
		void _set(const CELL& c, v3i at) override
		{
			this->next().set(c, m_transformation.apply(at));
		}
		
		void _set(CELL&& c, v3i at) override
		{
			this->next().set(std::move(c), m_transformation.apply(at));
		}
	
	public:
		void clear() override
		{
			this->next().clear();
		}
	
	
	public:
		explicit TransformedMap(IMap<CELL>* map) : MapDecorator<CELL>(map) { }
		~TransformedMap() = default;
		
		
	public:
		inline void reset_transform() { m_transformation = {}; }
		inline void set_transformation(const Transformation& transformation) { m_transformation = transformation; }
		inline void add_transformation(const Transformation& transformation) { m_transformation += transformation; }
		inline void rem_transformation(const Transformation& transformation) { m_transformation -= transformation; }
		inline void set_transformation(Direction dir, v3i offset) { m_transformation = { dir, offset }; }
		inline const Transformation& get_transformation() const { return m_transformation; }
	};
}


#endif