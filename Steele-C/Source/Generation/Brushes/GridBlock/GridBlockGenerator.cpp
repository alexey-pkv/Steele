#include "GridBlockGenerator.h"
#include "LocationMap.h"


void Steele::GridBlockGenerator::init()
{
	int wallSize = m_config->max();
	
	for (auto x = -wallSize; x < m_config->GridWidth + wallSize; x++)
	{
		for (auto y = -wallSize; y < m_config->GridHeight + wallSize; y++)
		{
			m_region.set(&m_zero, x, y);
		}
	}
	
	for (auto x = 0; x < m_config->GridWidth; x++)
	{
		for (auto y = 0; y < m_config->GridHeight; y++)
		{
			m_region.set(nullptr, x, y);
		}
	}
}

void Steele::GridBlockGenerator::place_block(r2i at)
{
	r2i& block = m_blocks.emplace_back(at);
	
	m_locations.placed(block);
	
	auto from = block.position;
	auto to = block.position + block.size;
	
	for (int x = from.x; x < to.x; x++)
	{
		for (int y = from.y; y < to.y; y++)
		{
			m_region.set(&block, { x, y });
		}
	}
}

bool Steele::GridBlockGenerator::generate_block(v2i block)
{
	auto map = m_locations.get_map(block);
	
	if (!map || map->is_empty())
		return false;
	
	int		index		= m_rng->next_int_32(0, (int)map->size() - 1);
	v2i		pos			= map->get_at(index);
	
	place_block(r2i(pos, block));
	
	return true;
}

bool Steele::GridBlockGenerator::place_mins()
{
	for (auto& b : m_config->Blocks)
	{
		for (auto i = 0; i < b.Min; i++)
		{
			if (!generate_block(b.Size))
			{
				return false;
			}
			
			b.add_generated();
		}
	}
	
	return true;
}


Steele::BlockTypeConfig* Steele::GridBlockGenerator::get_next_block(std::vector<BlockTypeConfig>& list, int weight)
{
	int next = m_rng->next_int_32(1, weight);
	
	for (auto& b : list)
	{
		next -= b.Weight;
		
		if (next <= 0)
		{
			return &b;
		}
	}
	
	return nullptr;
}


bool Steele::GridBlockGenerator::place_blocks()
{
	int weight = m_config->total_weight();
	auto blocks = m_config->Blocks;
	
	while (!blocks.empty() && !m_locations.is_empty() && weight > 0)
	{
		auto block = get_next_block(blocks, weight);
		
		if (!block) return false;
		
		if (m_locations.has_map(block->Size))
		{
			generate_block(block->Size);
			block->add_generated();
		}
		
		if (block->is_at_max() || 
			!m_locations.has_map(block->Size))
		{
			weight -= block->Weight;
			remove_where(blocks, [&] (auto& b) { return b.Size == block->Size; });
		}
	}
	
	return true;
}

bool Steele::GridBlockGenerator::generate(IRNG& rng, Steele::BlockGeneratorConfig& config)
{
	m_config = &config;
	m_rng = &rng;
	
	m_locations.init(config);
	
	init();
	
	if (!place_mins())
		return false;
	
	if (!place_blocks())
		return false;
	
	place_unit_blocks();
	
	return true;
}

void Steele::GridBlockGenerator::place_unit_blocks()
{
	auto oneMap = m_locations.get_map(v2i_one);
	
	if (!oneMap)
		return;
	
	for (auto i : oneMap->placements())
	{
		place_block(r2i(i, v2i_one));
	}
}

std::string Steele::GridBlockGenerator::debug_map() const
{
	v2i from	= v2i_zero;
	v2i to		= v2i(m_config->GridWidth * 2 + 1, m_config->GridHeight * 2 + 1);
	
	std::map<v2i, char> data;
	
	// Init 
	for (auto x = from.x; x < to.x; x++)
	{
		for (auto y = from.y; y < to.y; y++)
		{
			char c = ' ';
			
			if (x % 2 == 0)
			{
				if (y % 2 == 0)
				{
					c = '+';
				}
				else
				{
					c = '-';
				}
			}
			else if (y % 2 == 0)
			{
				c = '|';
			}
			
			data[{x, y}] = c;
		}
	}
	
	
	// Paint
	for (auto x = from.x + 3; x < to.x; x += 2)
	{
		for (auto y = from.y + 1; y < to.y; y += 2)
		{
			auto curr_v = v2i {(x - 1) / 2, (y - 1) / 2};
			auto curr = m_region.try_get(curr_v);
			auto left = m_region.try_get(curr_v - v2i { 1, 0 });
			
			if (!curr || !left || *curr == nullptr || *left == nullptr)
				continue;
			
			if (*curr == *left)
			{
				data[{x - 1, y}] = ' ';
			}
		}
	}
	
	for (auto x = from.x + 1; x < to.x; x += 2)
	{
		for (auto y = from.y + 3; y < to.y; y += 2)
		{
			auto curr_v = v2i {(x - 1) / 2, (y - 1) / 2};
			auto curr = m_region.try_get(curr_v);
			auto top = m_region.try_get(curr_v - v2i { 0, 1 });
			
			if (!curr || !top || *curr == nullptr || *top == nullptr)
				continue;
			
			if (*curr == *top)
			{
				data[{x, y - 1}] = ' ';
			}
		}
	}
	
	for (auto x = from.x + 3; x < to.x; x += 2)
	{
		for (auto y = from.y + 3; y < to.y; y += 2)
		{
			auto curr_v = v2i {(x - 1) / 2, (y - 1) / 2};
			auto curr = m_region.try_get(curr_v);
			auto top_left = m_region.try_get(curr_v - v2i { 1, 1 });
			
			if (!curr || !top_left || *curr == nullptr || *top_left == nullptr)
				continue;
			
			if (*curr == *top_left)
			{
				data[{x - 1, y - 1}] = ' ';
			}
		}
	}
	
	
	// Print
	std::string result;
	
	for (auto x = 0; x < to.x; x++)
	{
		for (auto y = 0; y < to.y; y++)
		{
			result += data[{ x, y }];
		}
		
		result += '\n';
	}
	
	return result;
}
