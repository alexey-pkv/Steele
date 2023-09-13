#include "GodotTestPlugin.h"


using namespace godot;


void GodotTestPlugin::_bind_methods()
{
	
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
	m_i = i;
}
