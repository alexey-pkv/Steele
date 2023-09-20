#ifndef STEELE_BLOCKTYPELOCATIONMAP_H
#define STEELE_BLOCKTYPELOCATIONMAP_H


#include <set>

#include "DataTypes/Types.h"
#include "Utils.h"


namespace Steele
{
	class BlockTypeLocationMap
	{
	private:
		v2i				m_block;
		std::set<v2i>	m_placement;
		
		
	public:
		BlockTypeLocationMap(v2i block, r2i mapSize);
		
		
	public:
		inline const v2i& block() const { return m_block; }
		inline const std::set<v2i>& placements() const { return m_placement; }
		inline bool is_empty() const { return m_placement.empty(); }
		inline size_t size() const { return m_placement.size(); }
		inline bool has(v2i pos) const { return contains(m_placement, pos); }
		
		
	public:
		v2i get_at(int index) const;
		void placed(r2i block);
	};
}


#endif