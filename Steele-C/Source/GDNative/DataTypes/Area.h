#ifndef GODOT_AREA_H
#define GODOT_AREA_H



#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include "DataTypes/Area.h"


namespace godot
{
	class Area : public RefCounted
	{
		GDCLASS(Area, RefCounted) // NOLINT(*-use-auto)
	private:
		Steele::Area m_area;


	public:
		static void _bind_methods();

	public:

		Area() = default;
		Area(const Area&) = default;
		Area(Area&&) = default;
		Area(const Steele::Area& a);
		Area(Steele::Area&& a);

		~Area() override = default;

	public:
		int height() const;
		int width() const;
		int top() const;
		int bottom() const;
		int right() const;
		int left() const;

		v2i get_offset() const;
		bool is_empty() const;

		void set_offset(int x, int y);
		void set_offset_v2i(v2i v);
		void add_offset(int x, int y);
		void add_offset_v2i(const v2i& v);
		void reset_offset();
		Ref<Area> get_reset_offset_area() const;

		Rect2i GetRect() const;

		bool overlaps(const Ref<Area>& a) const;

		godot::String debug_info() const;
		godot::String debug_info_extended(int fill, int empty, bool withBoarder = true) const;

	public:
		bool is_equal(const Ref<Area>& a) const;

		void intersect_v2i(const v2i& v);
		void intersect_a(const Ref<Area>& a);
		void intersect_r2i(const Rect2i& r);

		void combine_v2i(const v2i& v);
		void combine_a(const Ref<Area>& a);
		void combine_r2i(const Rect2i& r);

	public:
		static Ref<Area> from_string(const godot::String& str);
		static Ref<Area> ZERO();
		static Ref<Area> ONE();
	};
}

#endif //GODOT_AREA_H
