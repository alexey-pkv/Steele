#ifndef GODOT_RESOURCE_DB_NODE_H
#define GODOT_RESOURCE_DB_NODE_H


#include <godot.hpp>
#include <godot_cpp/classes/node.hpp>

#include "Utils.h"
#include "DataTypes/Generation/GenerationResourcesDB.h"
#include "GDNative/Common/ResourceObject.h"
#include "GDNative/Generation/Brushes/FillBrush.h"


namespace godot
{
	class ResourcesDBNode : public Node
	{
		GDCLASS(ResourcesDBNode, Node) // NOLINT(*-use-auto)
	private:
		sptr<Steele::GenerationResourcesDB> m_db;
		
		
	private:
		template<class T>
		inline void add_brush_resource(t_id id, Ref<T> r)
		{
			if (r.is_null())
			{
				m_db->remove(id);
				return;
			}
			
			m_db->brushes().set(id, r->steele_ptr());
			r->link().set(id, m_db);
		}
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		ResourcesDBNode();
		~ResourcesDBNode() override = default;
		
		
	public:
		void clear();
		int count() const;
		bool has(t_id id) const;
		
		
	public:
		void add_fill_brush(t_id id, const Ref<FillBrush>& brush);
		
		
	public: // Steele Methods
		inline sptr<Steele::GenerationResourcesDB> db() { return m_db; }
		inline sptr<const Steele::GenerationResourcesDB> db() const { return m_db; }
	};
}


#endif