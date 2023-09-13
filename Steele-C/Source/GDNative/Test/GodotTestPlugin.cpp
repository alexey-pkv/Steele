#include "GodotTestPlugin.h"


using namespace godot;


void GodotTestPlugin::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_value"), &GodotTestPlugin::get_value);
	ClassDB::bind_method(D_METHOD("set_value", "i"), &GodotTestPlugin::set_value);
}


GodotTestPlugin::GodotTestPlugin() : 
	m_i(12)
{
	
}


void GodotTestPlugin::_init()
{
	
}

int GodotTestPlugin::get_value() const
{
	
	return m_i;
}

void GodotTestPlugin::set_value(int i)
{
	m_i = i * 2;
}
