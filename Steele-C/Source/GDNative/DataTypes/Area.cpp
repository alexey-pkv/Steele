#include "Area.h"


void Area::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("height"), &Area::height);
	ClassDB::bind_method(D_METHOD("width"), &Area::width);
	ClassDB::bind_method(D_METHOD("top"), &Area::top);
	ClassDB::bind_method(D_METHOD("bottom"), &Area::bottom);
	ClassDB::bind_method(D_METHOD("right"), &Area::right);
	ClassDB::bind_method(D_METHOD("left"), &Area::left);
	ClassDB::bind_method(D_METHOD("get_offset"), &Area::get_offset);
	ClassDB::bind_method(D_METHOD("is_empty"), &Area::is_empty);
	ClassDB::bind_method(D_METHOD("set_offset", "x", "y"), &Area::set_offset);
	ClassDB::bind_method(D_METHOD("set_offset_v2i", "v"), &Area::set_offset_v2i);
	ClassDB::bind_method(D_METHOD("add_offset", "x", "y"), &Area::add_offset);
	ClassDB::bind_method(D_METHOD("add_offset_v2i", "v"), &Area::add_offset_v2i);
	ClassDB::bind_method(D_METHOD("reset_offset"), &Area::reset_offset);
	ClassDB::bind_method(D_METHOD("get_reset_offset_area"), &Area::get_reset_offset_area);
	ClassDB::bind_method(D_METHOD("get_rect"), &Area::GetRect);
	ClassDB::bind_method(D_METHOD("overlaps"), &Area::overlaps);
	ClassDB::bind_method(D_METHOD("debug_info"), &Area::debug_info);
	ClassDB::bind_method(D_METHOD("debug_info_extended", "fill", "empty", "withBorders"), &Area::debug_info_extended);
	ClassDB::bind_method(D_METHOD("is_equal", "a"), &Area::is_equal);
	ClassDB::bind_method(D_METHOD("intersect_v2i", "v"), &Area::intersect_v2i);
	ClassDB::bind_method(D_METHOD("intersect_a", "a"), &Area::intersect_a);
	ClassDB::bind_method(D_METHOD("intersect_r2i", "r"), &Area::intersect_r2i);
	ClassDB::bind_method(D_METHOD("combine_v2i", "v"), &Area::combine_v2i);
	ClassDB::bind_method(D_METHOD("combine_a", "v"), &Area::combine_a);
	ClassDB::bind_method(D_METHOD("combine_r2i", "r"), &Area::combine_r2i);

	ClassDB::bind_static_method(get_class_static(), D_METHOD("from_string", "str"), &Area::from_string);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("ZERO"), &Area::ZERO);
	ClassDB::bind_static_method(get_class_static(), D_METHOD("ONE"), &Area::ONE);
}


Area::Area(const Steele::Area& a):
	m_area(a)
{}

Area::Area(Steele::Area &&a):
	m_area(std::move(a))
{}
                                                                         
int Area::height() const { return m_area.height(); }
int Area::width() const { return m_area.width(); }
int Area::top() const { return m_area.top(); }
int Area::bottom() const { return m_area.bottom(); }
int Area::right() const { return m_area.right(); }
int Area::left() const { return m_area.left(); }

v2i Area::get_offset() const { return m_area.offset(); }
bool Area::is_empty() const { return m_area.is_empty();}
void Area::set_offset(int x, int y) { m_area.set_offset(x, y); }
void Area::set_offset_v2i(v2i v) { m_area.set_offset(v); }
void Area::add_offset(int x, int y) { m_area.add_offset(x, y); }
void Area::add_offset_v2i(const v2i &v) { m_area.add_offset(v); }
void Area::reset_offset() { m_area.reset_offset(); }

Ref<Area> Area::get_reset_offset_area() const
{
	Ref<Area> a;

	a.instantiate();
	a->m_area = m_area.get_reset_offset_area();

	return a;
}

Rect2i Area::GetRect() const { return m_area.get_rect(); }
bool Area::overlaps(const Ref<Area>& a) const { return m_area.overlaps(a->m_area); }
godot::String Area::debug_info() const { return { m_area.debug_info().c_str() }; }
godot::String Area::debug_info_extended(int fill, int empty, bool withBoarder) const { return { m_area.debug_info((char)fill, (char)empty, withBoarder).c_str() }; }

bool Area::is_equal(const Ref<Area> &a) const { return m_area == a->m_area; }
void Area::intersect_v2i(const v2i &v) { m_area &= Steele::Area(v); }
void Area::intersect_a(const Ref<Area> &a) { m_area &= a->m_area; }
void Area::intersect_r2i(const Rect2i &r) { m_area &= Steele::Area(r); }
void Area::combine_v2i(const v2i &v) { m_area |= Steele::Area(v); }
void Area::combine_a(const Ref<Area> &a) { m_area |= a->m_area; }
void Area::combine_r2i(const Rect2i &r) { m_area |= Steele::Area(r); }


Ref<Area> Area::from_string(const godot::String &str)
{
	Ref<Area> a;

	a.instantiate();
	a->m_area = Steele::Area(str.utf8().get_data());

	return a;
}

Ref<Area> Area::ZERO() { return {}; }
Ref<Area> Area::ONE() { return Area::from_string("*\n"); }
