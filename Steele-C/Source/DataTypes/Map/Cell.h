#ifndef STEELE_CELL_H
#define STEELE_CELL_H


#include "Ground.h"

#include <vector>


namespace Steele
{
	class Cell
	{
	public:
		Steele::Ground	Ground = {};
		bool			IsRoad = false;
	
	
	public:
		~Cell() = default;
		
		Cell() = default;
		Cell(const Cell& cell) = default;
		Cell(Cell&& cell) = default;
		
		Cell& operator=(const Cell& cell) = default;
		Cell& operator=(Cell&&) = default;
		
		explicit Cell(const GroundTile &gt);
		explicit Cell(t_id id, Direction d, uint8_t index);
		
	
	public:
		inline void add_ground_tile(const GroundTile& tile) { Ground.add(tile); }
		inline bool remove_ground_tile(const GroundTile& tile) { return Ground.remove(tile); }
		
		
	public:
		inline void clear() { Ground.clear(); }
		
		
	public: // JSON
		void json_write(nlohmann::json& into) const;
		void json_read(const nlohmann::json& from);
	};
}


#endif