#include "RandomState.h"


#include <utility>


void godot::RandomState::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_seed"), &RandomState::get_seed);
	ClassDB::bind_method(D_METHOD("get_reference_type"), &RandomState::get_reference_type);
	ClassDB::bind_method(D_METHOD("has_reference"), &RandomState::has_reference);
	
	// Get Reference
	ClassDB::bind_method(D_METHOD("get_reference_i"), &RandomState::get_reference_i);
	ClassDB::bind_method(D_METHOD("get_reference_f"), &RandomState::get_reference_f);
	ClassDB::bind_method(D_METHOD("get_reference_v2i"), &RandomState::get_reference_i);
	ClassDB::bind_method(D_METHOD("get_reference_v3i"), &RandomState::get_reference_i);
	
	BIND_CONSTANT(REF_NONE)
	BIND_CONSTANT(REF_INT32)
	BIND_CONSTANT(REF_FLOAT)
	BIND_CONSTANT(REF_V2I)
	BIND_CONSTANT(REF_V3I)
}


godot::RandomState::RandomState(Steele::RandomState st) : m_state(std::move(st))
{
	
}


godot::String godot::RandomState::get_seed() const
{
	return {m_state.Seed.c_str()};
}

int godot::RandomState::get_reference_type() const
{
	return (int)m_state.Reference.Type;
}

int godot::RandomState::get_reference_i() const
{
	return m_state.Reference.Type == Steele::ReferenceValue::RefType::INT32 ? m_state.Reference.Reference.Int32 : 0;
}

float godot::RandomState::get_reference_f() const
{
	return m_state.Reference.Type == Steele::ReferenceValue::RefType::FLOAT ? m_state.Reference.Reference.Float : 0;
}

v2i godot::RandomState::get_reference_v2i() const
{
	return m_state.Reference.Type == Steele::ReferenceValue::RefType::V2I ? m_state.Reference.Reference.Vector2i : v2i_zero;
}

v3i godot::RandomState::get_reference_v3i() const
{
	return m_state.Reference.Type == Steele::ReferenceValue::RefType::V3I ? m_state.Reference.Reference.Vector3i : v3i_zero;
}
		
bool godot::RandomState::has_reference() const
{
	return m_state.has_reference();
}
