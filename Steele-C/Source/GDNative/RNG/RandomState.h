#ifndef GODOT_RANDOMSTATE_H
#define GODOT_RANDOMSTATE_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/RNG/RandomState.h"


namespace godot
{
	class RandomState : public RefCounted
	{
		GDCLASS(RandomState, RefCounted) // NOLINT(*-use-auto)
	private:
		Steele::RandomState m_state;
		
		
	public:
    	static void _bind_methods();
		
		
	public:
		explicit RandomState(Steele::RandomState st);
		
		RandomState() = default;
		RandomState(const RandomState&) = default;
		RandomState(RandomState&&) = default;
		
    	~RandomState() override = default;
		
		
	public:
		inline const Steele::RandomState& get_steele_state() const { return m_state; }
		inline void set_steele_state(const Steele::RandomState& state) { m_state = state; }
		inline void set_steele_state(Steele::RandomState&& state) { m_state = std::move(state); }
		
		
	public:
		String get_seed() const;
		int get_reference_type() const;
		
		int get_reference_i() const;
		float get_reference_f() const;
		v2i get_reference_v2i() const;
		v3i get_reference_v3i() const;
		
		bool has_reference() const;
		
		
	public:
		enum RefType : int
		{
			REF_NONE	= (int)Steele::ReferenceValue::RefType::NONE,
			REF_INT32	= (int)Steele::ReferenceValue::RefType::INT32,
			REF_FLOAT	= (int)Steele::ReferenceValue::RefType::FLOAT,
			REF_V2I		= (int)Steele::ReferenceValue::RefType::V2I,
			REF_V3I		= (int)Steele::ReferenceValue::RefType::V3I,
		};
	};
}
	

VARIANT_ENUM_CAST(RandomState::RefType);


#endif