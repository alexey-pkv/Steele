#include "LocationMap.h"


Steele::LocationMap::LocationMap(r2i mapSize, const std::vector<v2i>& blocks)
{
	init(mapSize, blocks);
}

Steele::LocationMap::LocationMap(const Steele::BlockGeneratorConfig& config)
{
	init(config);
}


void Steele::LocationMap::init(r2i mapSize, const std::vector<v2i>& blocks)
{
	for (auto& b : blocks)
	{
		m_byBlock.emplace_back(b, mapSize);
	}
}

void Steele::LocationMap::init(const Steele::BlockGeneratorConfig& config)
{
	std::vector<v2i> blocks = {};
	
	blocks.reserve(config.Blocks.size());
	
	for (auto& s : config.Blocks)
	{
		blocks.push_back(s.Size);
	}
	
	init(
		{0, 0, config.GridWidth, config.GridHeight},
		blocks
	);
}

void Steele::LocationMap::placed(r2i block)
{
	bool cleanup = false;
	
	for (auto& b : m_byBlock)
	{
		b.placed(block);
		
		if (b.is_empty())
		{
			cleanup = true;
		}
	}
	
	if (cleanup)
	{
		remove_where(m_byBlock, [](auto& b) { return b.is_empty(); });
	}
}

Steele::BlockTypeLocationMap* Steele::LocationMap::get_map(v2i blockType)
{
	for (auto& b : m_byBlock)
	{
		if (b.block() == blockType)
		{
			return &b;
		}
	}
	
	return nullptr;
}


bool Steele::LocationMap::has_map(v2i blockType) const
{
	for (auto& b : m_byBlock)
	{
		if (b.block() == blockType)
		{
			return true;
		}
	}
	
	return false;
}
