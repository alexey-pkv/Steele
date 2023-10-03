#ifndef GODOT_IDMAP_H
#define GODOT_IDMAP_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/IDMap.h"


namespace godot
{
	class IDMap : public RefCounted
	{
		GDCLASS(IDMap, RefCounted) // NOLINT(*-use-auto)
	private:
		Steele::IDMap m_map;
		
	
	public:
    	static void _bind_methods();
		
		
	public:
		~IDMap() override = default;
		IDMap() = default;
		
		
	public:
		bool has_id(int id) const;
		bool has_name(const String& s) const;
		int get_id(const String& s) const;
		String get_name(int id) const;

		int add(const String& name);
		bool update(int id, const String& newName);
		bool remove_by_id(int id);
		bool remove_by_name(const String& name);
		
		
	public:
		inline Steele::IDMap& source() { return m_map; }
		inline const Steele::IDMap& source() const { return m_map; }
	};
}


#endif