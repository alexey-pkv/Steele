#ifndef STEELE_ABSTRACTGENERATIONMAP_H
#define STEELE_ABSTRACTGENERATIONMAP_H


#include "ITransformable.h"
#include "TransformationStack.h"

#include "Base/Map/SimpleMap.h"
#include "Base/Map/StackedMap.h"
#include "Base/Map/TransformedMap.h"

#include "DataTypes/Map/Cell.h"
#include "Base/Generation/IGenerationMap.h"


namespace Steele
{
	template<typename CELL>
	class AbstractGenerationMap : public IGenerationMap<CELL>
	{
	private:
		SimpleMap<CELL>			m_map = {};
		TransformedMap<CELL>	m_transformed;
		StackedMap<CELL>		m_stacked;
		TransformationStack		m_transformations;
		
		
	public:
		AbstractGenerationMap() : 
			m_transformed(m_map),
			m_stacked(m_transformed) {}
		
		~AbstractGenerationMap() = default;
		
		
	public: // IMap 
		void clear() override
		{
			m_stacked.clear();
		}
	
	
	protected:
		CELL* _try_get(v3i at) override
		{
			return m_stacked.try_get(at);
		}
		
		const CELL* _try_get(v3i at) const override
		{
			return m_stacked.try_get(at);
		}
		
		CELL* _get(v3i at) override
		{
			return m_stacked.get(at);
		}
		
		void _set(const CELL& c, v3i at) override
		{
			m_stacked.set(c, at);
		}
		
		void _set(CELL&& c, v3i at) override
		{
			m_stacked.set(std::move(c), at);
		}
		
		bool _is_empty(v3i at) const override
		{
			return m_stacked.is_empty(at);
		}
		
		bool _remove(v3i at) override
		{
			return m_stacked.remove(at);
		}

	public: // IStackableMap
		void checkpoint() override { m_stacked.checkpoint(); }
		void rollback() override { m_stacked.rollback(); }
		void commit() override { m_stacked.commit(); }
		bool is_in_checkpoint() const override { return m_stacked.is_in_checkpoint(); }
		int stack_depth() const override { return m_stacked.stack_depth(); }
		
		
	public: // ITransformable
		void reset_transformation() override { m_transformations.clear(); m_transformed.reset_transform(); }
		bool is_transformed() const override { return m_transformations.is_transformed(); }
		Steele::Transformation peek_transformation() const override { return m_transformations.top(); }
		const Steele::Transformation& transformation() const override { return m_transformations.current(); }
		
		void pop_transformation() override
		{
			m_transformations.pop(); 
			m_transformed.set_transformation(m_transformations.current());
		}
		
		
	protected: // ITransformable
		void _push_transformation(const Steele::Transformation& t) override
		{
			m_transformations.push(t); 
			m_transformed.set_transformation(m_transformations.current());
		}
	};
}


#endif