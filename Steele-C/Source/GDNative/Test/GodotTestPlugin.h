#ifndef GODOT_GODOTTESTPLUGIN_H
#define GODOT_GODOTTESTPLUGIN_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include "godot_cpp/classes/node.hpp"


namespace godot
{
	class GodotTestPlugin : public RefCounted
	{
		GDCLASS(GodotTestPlugin, RefCounted) // NOLINT(*-use-auto)
	private:
		int m_i = 0;
		
	
	public:
		GodotTestPlugin();
    	~GodotTestPlugin() override = default;
		
		
	public:
		void _init();
		
		
	public:
		int get_value() const;
		void set_value(int i);
		int test_node(Node* n);
		
		
	public:
    	static void _bind_methods();
		
	};
}


#endif