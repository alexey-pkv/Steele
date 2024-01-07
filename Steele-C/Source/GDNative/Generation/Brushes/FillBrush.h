#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#ifndef GODOT_FILL_BRUSH_H
#define GODOT_FILL_BRUSH_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Generation/GenerationResourcesDB.h"
#include "GDNative/Common/ResourceObject.h"
#include "Generation/Brushes/FillBrush.h"


namespace godot
{
	class FillBrush : public RefCounted, public ResourceObject
	{
		GDCLASS(FillBrush, RefCounted)
	private:
		Steele::FillBrush m_brush;
		
	
	public:
    	static void _bind_methods();
		
		
	public:
		t_id get_ground_id() const;
		void set_ground_id(t_id id);

		t_id get_palette_id() const;
		void set_palette_id(t_id id);
		
		
	public:
		inline Steele::FillBrush* steele_ptr() { return &m_brush; }
		inline const Steele::FillBrush& steele_brush() const { return m_brush; }
	};
}


#endif

#pragma clang diagnostic pop