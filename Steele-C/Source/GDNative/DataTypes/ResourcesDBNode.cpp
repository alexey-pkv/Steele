#include "ResourcesDBNode.h"


using namespace godot;


void ResourcesDBNode::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("clear"),		&ResourcesDBNode::clear);
	ClassDB::bind_method(D_METHOD("count"),		&ResourcesDBNode::count);
	ClassDB::bind_method(D_METHOD("has", "id"),	&ResourcesDBNode::has);
	
	ClassDB::bind_method(D_METHOD("add_fill_brush", "id", "brush"), &ResourcesDBNode::add_fill_brush);
}


ResourcesDBNode::ResourcesDBNode() : 
	m_db(make_shared<Steele::GenerationResourcesDB>())
{
	
}


void ResourcesDBNode::clear()
{
	m_db->clear();
}

int ResourcesDBNode::count() const
{
	return m_db->count();
}

bool ResourcesDBNode::has(t_id id) const
{
	return m_db->has(id);
}


void ResourcesDBNode::add_fill_brush(t_id id, const Ref<FillBrush>& brush)
{
	add_brush_resource(id, brush);
}