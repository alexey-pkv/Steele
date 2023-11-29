#ifndef STEELE_MAPSTACK_H
#define STEELE_MAPSTACK_H


#include "IMap.h"
#include "MapDecorator.h"


namespace Steele
{
	template <typename CELL>
	class MapStack : public IMap<CELL>
	{
	private:
		IMap<CELL>*	m_head = nullptr;
		
	
	protected:
		CELL* _try_get(v3i at) override				{ return m_head->_try_get(at); }
		const CELL* _try_get(v3i at) const override { return m_head->_try_get(at); }
		CELL* _get(v3i at) override					{ return m_head->_get(at); }
		void _set(const CELL& c, v3i at) override	{ m_head->_set(c, at); }
		void _set(CELL&& c, v3i at) override		{ m_head->_set(c, at); }
		bool _is_empty(v3i at) const override		{ return m_head->_is_empty(at); }
		bool _remove(v3i at) override				{ return m_head->_remove(at); }
		
		
	public:
		void clear() override { m_head->clear(); }
		
		
	public:
		void setup(IMap<CELL>* root, std::vector<MapDecorator<CELL>*> decorators)
		{
			m_head = root;
			
			for (MapDecorator<CELL>* decorator : decorators)
			{
				add_child(decorator);
			}
		}
		
		void add_child(MapDecorator<CELL>* decorator)
		{
			if (m_head)
			{
				decorator->set_child(m_head);
			}
			
			m_head = decorator;
		}
	};
}


#endif