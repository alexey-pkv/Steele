#ifndef STEELE_CELL_H
#define STEELE_CELL_H


#include "Ground.h"

#include <vector>


namespace Steele
{
	struct Cell
	{
	public:
		std::vector<GroundTile>	Ground = {};
		
		bool	IsRoad = false;
	
	
	public:
		Cell() = default;
		Cell(const Cell& cell) = default;
		Cell(Cell&& cell) = default;
		Cell& operator=(const Cell& cell) = default;
		Cell& operator=(Cell&&) = default;
		
		~Cell() = default;
		
	
	public:
		void AddGroundTile(const GroundTile& tile);
		bool RemoveGroundTile(const GroundTile& tile);
		
		
	public:
		
		
	public:
		inline unsigned long GroundTilesCount() const { return Ground.size(); }
		inline void Clear() { Ground.clear(); }
	};
}


#endif