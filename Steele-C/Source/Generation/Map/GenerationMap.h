#ifndef STEELE_GENERATIONMAP_H
#define STEELE_GENERATIONMAP_H


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
		TransformedMap<CELL>	m_transformed;
		TransformationStack		m_transformations;
		
		
	public:
		AbstractGenerationMap(sptr<IMap<CELL>> map) : 
			m_transformed(map) {}
		
		~AbstractGenerationMap() = default;
		
		
	public: // IMap 
		void clear() override
		{
			m_transformed.clear();
		}
	
	
	protected:
		CELL* _try_get(v3i at) override
		{
			return m_transformed.try_get(at);
		}
		
		const CELL* _try_get(v3i at) const override
		{
			return m_transformed.try_get(at);
		}
		
		CELL* _get(v3i at) override
		{
			return m_transformed.get(at);
		}
		
		void _set(const CELL& c, v3i at) override
		{
			m_transformed.set(c, at);
		}
		
		void _set(CELL&& c, v3i at) override
		{
			m_transformed.set(std::move(c), at);
		}
		
		bool _is_empty(v3i at) const override
		{
			return m_transformed.is_empty(at);
		}
		
		bool _remove(v3i at) override
		{
			return m_transformed.remove(at);
		}
		
		
	public:
		size_t size() const override
		{
			return m_transformed.size();
		}
	
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
	
	
	class GenerationMap : public AbstractGenerationMap<Cell>
	{
	public:
		GenerationMap(sptr<IMap<Cell>> map);
		~GenerationMap() = default;
	};
}


#endif