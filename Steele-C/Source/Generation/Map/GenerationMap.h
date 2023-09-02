#ifndef STEELE_GENERATIONMAP_H
#define STEELE_GENERATIONMAP_H


#include "TransformationStack.h"
#include "DataTypes/Map/Cell.h"
#include "Base/Map/SimpleMap.h"
#include "Base/Map/StackedMap.h"
#include "Base/Map/TransformedMap.h"
#include "ITransformable.h"


namespace Steele
{
	class GenerationMap :
		public IMap<Cell>,
		public IStackableMap,
		public ITransformable
	{
	private:
		SimpleMap<Cell>			m_map = {};
		TransformedMap<Cell>	m_transformed;
		StackedMap<Cell>		m_stacked;
		TransformationStack		m_transformations;
		
		
	public:
		GenerationMap();
		~GenerationMap() = default;
		
		
		void clear() override;
	
	protected:
		Cell* _try_get(v3i at) override;
		const Cell* _try_get(v3i at) const override;
		Cell* _get(v3i at) override;
		void _set(const Cell& c, v3i at) override;
		void _set(Cell&& c, v3i at) override;
		bool _is_empty(v3i at) const override;
		bool _remove(v3i at) override;
	
	
	public: // IStackableMap
		void checkpoint() override;
		void rollback() override;
		void commit() override;
		int stack_depth() const override;
		bool is_in_checkpoint() const override;
		
		
	public: // ITransformable
		void pop_transformation() override;
		void reset_transformation() override;
		bool is_transformed() const override;
		Transformation peek_transformation() const override;
		const Transformation& transformation() const override;
	
	protected: // ITransformable
		void _push_transformation(const Transformation& t) override;
	};
}


#endif