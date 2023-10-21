#ifndef GODOT_CELL_H
#define GODOT_CELL_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include "DataTypes/Map/Cell.h"
#include "GroundTile.h"
#include "Ground.h"


namespace godot
{
	class Cell : public RefCounted
	{
		GDCLASS(Cell, RefCounted) // NOLINT(*-use-auto)

	private:
		Steele::Cell m_cell;
	
	
	public:
		static void _bind_methods();
	
	
	public:
		Cell() = default;
		Cell(const Cell&) = default;
		Cell(Cell&&) = default;

		~Cell() override = default;
		
		
	public:
		inline void set(const Steele::Cell* c) { m_cell = *c; }
		inline void set(const Steele::Cell& c) { m_cell = c; }
		inline Steele::Cell& steele_cell() { return m_cell; }
		inline const Steele::Cell& steele_cell() const { return m_cell; }
		

	public:
		Ref<Ground> get_ground() const;

		void add_ground_tile(const Ref<GroundTile>& tile);
		bool remove_ground_tile(const Ref<GroundTile>& tile);

		void clear();
	};
}


#endif //GODOT_CELL_H
