#ifndef STEELE_LOCATIONMAP_H
#define STEELE_LOCATIONMAP_H


#include "DataTypes/Types.h"
#include "BlockTypeLocationMap.h"
#include "BlockGeneratorConfig.h"


namespace Steele
{
	class LocationMap
	{
	private:
		std::vector<BlockTypeLocationMap>	m_byBlock = {};
		
		
	public:
		LocationMap() = default;
		LocationMap(r2i mapSize, const std::vector<v2i>& blocks);
		LocationMap(const BlockGeneratorConfig& config);
		
		
	public:
		void init(const BlockGeneratorConfig& config);
		void init(r2i mapSize, const std::vector<v2i>& blocks);
		void placed(r2i block);
		BlockTypeLocationMap* get_map(v2i blockType);
		bool has_map(v2i blockType) const;
		
		
	public:
		inline std::vector<BlockTypeLocationMap>& locations() { return m_byBlock; }
		inline bool is_empty() const { return m_byBlock.empty(); }
	};
}


#endif