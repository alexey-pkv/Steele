#ifndef STEELE_GRIDBLOCKGENERATOR_H
#define STEELE_GRIDBLOCKGENERATOR_H


#include <map>
#include <vector>

#include "BlockGeneratorConfig.h"
#include "Base/Map/SimpleMap.h"
#include "Base/RNG/IRNG.h"
#include "LocationMap.h"


namespace Steele
{
	class GridBlockGenerator
	{
	private:
		LocationMap m_locations {};
		
	private:
		typedef godot::Rect2i r2i;
		
		
	private:
		r2i						m_zero = { -1, -1, -1, -1 };
		std::vector<r2i>		m_blocks;
		SimpleMap<r2i*>			m_region;
		BlockGeneratorConfig*	m_config;
		IRNG*					m_rng;
		
		
	private:
		BlockTypeConfig* get_next_block(std::vector<BlockTypeConfig>& list, int weight);
		
		void init();
		void place_block(r2i at);
		bool generate_block(v2i block);
		bool place_mins();
		bool place_blocks();
		void place_unit_blocks();
		
		
	public:
		bool generate(IRNG& rng, BlockGeneratorConfig& config);
	
	public:
		std::string debug_map() const; 
	};
}


#endif