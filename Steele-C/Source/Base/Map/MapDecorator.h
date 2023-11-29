#ifndef STEELE_MAPDECORATOR_H
#define STEELE_MAPDECORATOR_H


#include "IMap.h"

namespace Steele
{
	template <typename CELL>
	class MapDecorator : public IMap<CELL>
	{
	private:
		IMap<CELL>* m_map;
		
	
	protected:
		IMap<CELL>& next() { return *m_map; }
		const IMap<CELL>& next() const { return *m_map; }
	
		
	public:
		explicit MapDecorator(IMap<CELL>* map) : m_map(map) { }
		
		MapDecorator() : m_map(nullptr) { }
		~MapDecorator() = default;
		
		
	public:
		inline void set_child(IMap<CELL>* map) { m_map = map; }
	};
}


#endif