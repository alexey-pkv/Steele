#ifndef STEELE_BLOCKGENERATORCONFIG_H
#define STEELE_BLOCKGENERATORCONFIG_H


#include <vector>

#include "BlockTypeConfig.h"


namespace Steele
{
	struct BlockGeneratorConfig
	{
	public:
		int GridWidth;
		int GridHeight;
		int SingleBlockSize;
		int RoadWidth;
		
		std::vector<BlockTypeConfig> Blocks;
		
		
	public:
		int total_weight() const;
		
		
	public:
		inline void add_block(BlockTypeConfig config) { Blocks.push_back(config); }
		inline void add_block(v2i size, int weight, int min = -1, int max = -1)
		{
			Blocks.push_back(BlockTypeConfig {
				.Size = size,
				.Min = min,
				.Max = max,
				.Weight = weight,
			});
		}
		
		inline int max() const
		{
			auto max = -1;
			
			for (auto& c : Blocks)
			{
				max = std::max(max, c.Max);
				max = std::max(max, c.Min);
			}
			
			return max;
		}
	};
}


#endif