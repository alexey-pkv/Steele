#ifndef STEELE_GODOTTESTPLUGIN_H
#define STEELE_GODOTTESTPLUGIN_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>


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
		
		
	public:
    	static void _bind_methods();
		
	};
}


#endif