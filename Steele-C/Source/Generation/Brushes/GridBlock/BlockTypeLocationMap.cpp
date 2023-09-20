#include "BlockTypeLocationMap.h"


Steele::BlockTypeLocationMap::BlockTypeLocationMap(v2i block, r2i mapSize) : 
	m_block(block),
	m_placement()
{
	v2i placementSize = mapSize.size - block + v2i_one;
	
	if (placementSize.x <= 0 || placementSize.y <= 0)
		return;
	
	for (auto x = 0; x < placementSize.x; x++)
	{
		for (auto y = 0; y < placementSize.y; y++)
		{
			m_placement.insert(mapSize.position + v2i {x, y});
		}
	}
}


v2i Steele::BlockTypeLocationMap::get_at(int index) const
{
	if (index >= m_placement.size())
		return v2i_zero;
	
	auto target = m_placement.begin();
	
	std::advance(target, index);
	
	return *target;
}

void Steele::BlockTypeLocationMap::placed(r2i block)
{
	v2i from = block.position - m_block + v2i_one;
	v2i to = block.position + block.size;
	
	for (auto x = from.x; x < to.x; x++)
	{
		for (auto y = from.y; y < to.y; y++)
		{
			m_placement.erase(v2i { x, y });
		}
	}
}
