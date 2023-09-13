#ifndef GODOT_XOROSHIRORNG_H
#define GODOT_XOROSHIRORNG_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>


#include <RNG/XoroshiroRNG.h>
#include "RandomState.h"


namespace godot
{
	class XoroshiroRNG : public RefCounted
	{
		GDCLASS(XoroshiroRNG, RefCounted) // NOLINT(*-use-auto)
	private:
		Steele::XoroshiroRNG	m_rng;
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		XoroshiroRNG();
    	~XoroshiroRNG() override = default;
		
		
	public:
		void _init();
		
		
	public:	// Methods
		int		next_int();
		int		next_int_r(int min, int max);
		bool	next_bool();
		float	next_float();
		float	next_float_r(float min, float max);
		
		
	public:	// Properties
		void jump(int count);
		String get_seed() const;
		
		void reset();
		void reset_seed(const String& str);
		
		Ref<RandomState> get_state() const;
		void set_state(const Ref<RandomState>& rs);
	};
}


#endif