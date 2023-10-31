#include "XoroshiroRNG.h"


using namespace godot;


void XoroshiroRNG::_bind_methods()
{
	// Random
	ClassDB::bind_method(D_METHOD("next_int"), &XoroshiroRNG::next_int);
	ClassDB::bind_method(D_METHOD("next_int_r", "min", "max"), &XoroshiroRNG::next_int_r);
	ClassDB::bind_method(D_METHOD("next_bool"), &XoroshiroRNG::next_bool);
	ClassDB::bind_method(D_METHOD("next_float"), &XoroshiroRNG::next_float);
	ClassDB::bind_method(D_METHOD("next_float_r", "min", "max"), &XoroshiroRNG::next_float_r);
	
	// Other
	ClassDB::bind_method(D_METHOD("get_seed"), &XoroshiroRNG::get_seed);
	ClassDB::bind_method(D_METHOD("jump", "i"), &XoroshiroRNG::jump);
	ClassDB::bind_method(D_METHOD("reset"), &XoroshiroRNG::reset);
	ClassDB::bind_method(D_METHOD("reset_seed", "seed"), &XoroshiroRNG::reset_seed);
	
	// State
	ClassDB::bind_method(D_METHOD("get_state"), &XoroshiroRNG::get_state);
	ClassDB::bind_method(D_METHOD("set_state", "state"), &XoroshiroRNG::set_state);
	
	ClassDB::bind_method(D_METHOD("reset_to_reference_i", "value"), &XoroshiroRNG::reset_to_reference_i);
	ClassDB::bind_method(D_METHOD("reset_to_reference_f", "value"), &XoroshiroRNG::reset_to_reference_f);
	ClassDB::bind_method(D_METHOD("reset_to_reference_v2i", "value"), &XoroshiroRNG::reset_to_reference_v2i);
	ClassDB::bind_method(D_METHOD("reset_to_reference_v3i", "value"), &XoroshiroRNG::reset_to_reference_v3i);
}


XoroshiroRNG::XoroshiroRNG()
{
	m_rng.reset_state();
}


void XoroshiroRNG::_init()
{
	
}


int XoroshiroRNG::next_int()
{
	return m_rng.next_int_32();
}

int XoroshiroRNG::next_int_r(int min, int max)
{
	if (min > max)
		std::swap(min, max);
	
	return m_rng.next_int_32(min, max);
}

bool XoroshiroRNG::next_bool()
{
	return m_rng.next_bool();
}

float XoroshiroRNG::next_float()
{
	return (float)m_rng.next_double();
}

float XoroshiroRNG::next_float_r(float min, float max)
{
	return (float)m_rng.next_double(min, max);
}

void XoroshiroRNG::jump(int i)
{
	return m_rng.jump(i);
}

godot::String XoroshiroRNG::get_seed() const
{
	return {m_rng.get_seed().c_str()};
}

void XoroshiroRNG::reset()
{
	m_rng.reset_state();
}

void XoroshiroRNG::reset_seed(const godot::String& str)
{
	m_rng.reset_state(str.utf8().get_data());
}


Ref<RandomState> XoroshiroRNG::get_state() const
{
	Ref<RandomState> state;
	
	state.instantiate();
	state->set_steele_state(m_rng.get_state());
	
	return state;
}

void XoroshiroRNG::set_state(const Ref<RandomState>& rs)
{
	m_rng.set_state(rs->get_steele_state());
}


void XoroshiroRNG::reset_to_reference_i(int to)
{
	reset_to_reference_T(to);
}

void XoroshiroRNG::reset_to_reference_f(float to)
{
	reset_to_reference_T(to);
}

void XoroshiroRNG::reset_to_reference_v2i(v2i to)
{
	reset_to_reference_T(to);
}

void XoroshiroRNG::reset_to_reference_v3i(v3i to)
{
	reset_to_reference_T(to);
}