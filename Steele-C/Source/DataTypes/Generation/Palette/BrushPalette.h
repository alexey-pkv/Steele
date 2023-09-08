#ifndef STEELE_BRUSHPALETTE_H
#define STEELE_BRUSHPALETTE_H


#include <map>

#include "Utils.h"
#include "DataTypes/Types.h"


namespace Steele
{
	class IBrush;
	
	
	class BrushPalette
	{
	private:
		std::map<t_id, sptr<IBrush>>	m_brushes;
		
		
	public:
		sptr<IBrush> get(t_id id);
		sptr<const IBrush> get(t_id id) const;
		
		void add(t_id id, sptr<IBrush> brush);
		
		
	public:
		inline size_t size() { return m_brushes.size(); }
		inline bool has(t_id id) { return contains(m_brushes, id); }
	};
}


#endif