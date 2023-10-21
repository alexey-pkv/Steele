#ifndef GODOT_IDMAP_H
#define GODOT_IDMAP_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/IDMap.h"


namespace godot
{
	class IDMap : public Object
	{
		GDCLASS(IDMap, Object) // NOLINT(*-use-auto)
	private:
		inline static Steele::IDMap& map() { return Steele::IDMap::global(); };
		
	
	public:
    	static void _bind_methods();
		
		
	public:
		static bool has_id(int id);
		static bool has_name(const String& s);
		static int get_id(const String& s);
		static String get_name(int id);

		static int add(const String& name);
		static bool update(int id, const String& newName);
		static bool remove_by_id(int id);
		static bool remove_by_name(const String& name);
	};
}


#endif