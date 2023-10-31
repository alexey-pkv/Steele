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
		
		
	public:	// State
		void jump(int count);
		String get_seed() const;
		
		void reset();
		void reset_seed(const String& str);
		
		Ref<RandomState> get_state() const;
		void set_state(const Ref<RandomState>& rs);
		
		void reset_to_reference_i(int to);
		void reset_to_reference_f(float to);
		void reset_to_reference_v2i(v2i to);
		void reset_to_reference_v3i(v3i to);
		
	
	private:
		template<class T>
		inline void reset_to_reference_T(T to)
		{
			auto state = m_rng.get_state();
			
			if (state.has_reference())
			{
				state.remove_reference();
				m_rng.set_state(state);
			}
			
			m_rng.reset_state();
			
			state = m_rng.create_referenced_state(to);
			m_rng.set_state(state);
		}
	};
}


#endif