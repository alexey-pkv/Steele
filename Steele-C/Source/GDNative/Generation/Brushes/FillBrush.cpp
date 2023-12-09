#include "FillBrush.h"


void FillBrush::_bind_methods()
{
	
	ClassDB::bind_method(D_METHOD("set_ground_id", "id"),	&FillBrush::set_ground_id);
	ClassDB::bind_method(D_METHOD("set_palette_id", "id"),	&FillBrush::set_palette_id);
	ClassDB::bind_method(D_METHOD("get_ground_id"), 		&FillBrush::get_ground_id);
	ClassDB::bind_method(D_METHOD("get_palette_id"), 		&FillBrush::get_palette_id);
}


void FillBrush::set_ground_id(t_id id) { m_brush.set_ground_id(id); }
void FillBrush::set_palette_id(t_id id) { m_brush.set_palette_id(id); }
t_id FillBrush::get_ground_id() const { return m_brush.get_ground_id(); }
t_id FillBrush::get_palette_id() const { return m_brush.get_palette_id(); }