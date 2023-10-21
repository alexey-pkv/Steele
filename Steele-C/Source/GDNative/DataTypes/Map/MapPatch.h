#ifndef STEELE_MAPPATCH_H
#define STEELE_MAPPATCH_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Map/Cell.h"
#include "Base/Map/SimpleMap.h"

#include "GDNative/DataTypes/Area.h"
#include "GDNative/DataTypes/Map/Cell.h"


namespace godot
{
	class MapPatch : public RefCounted
	{
		GDCLASS(MapPatch, RefCounted) // NOLINT(*-use-auto)
	public:
    	static void _bind_methods();
		
		
	private:
		Steele::SimpleMap<Steele::Cell>	m_patch;
	
		
	public:
		~MapPatch() override = default;
		MapPatch() = default;
		MapPatch(Steele::SimpleMap<Steele::Cell>& source);
		
		
	public:
		godot::Area area() const;
		int size() const;
		
		bool has(int x, int y, int z) const;
		bool has_v3i(v3i at) const;
		bool has_v2i(v2i at) const;
		
		Ref<Cell> get(int x, int y, int z) const;
		Ref<Cell> get_v3i(v3i at) const;
		Ref<Cell> get_v2i(v2i at) const;
		
		void get_c(int x, int y, int z, Ref<Cell>& into) const;
		void get_v3i_c(v3i at, Ref<Cell>& into) const;
		void get_v2i_c(v2i at, Ref<Cell>& into) const;
		
		void set(int x, int y, int z, const Ref<Cell>& cell);
		void set_v3i(v3i at, const Ref<Cell>& cell);
		void set_v2i(v2i at, const Ref<Cell>& cell);
		
		bool remove(int x, int y, int z);
		bool remove_v3i(v3i at);
		bool remove_v2i(v2i at);
	};
}


#endif