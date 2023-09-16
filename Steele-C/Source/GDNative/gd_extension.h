#ifndef GODOT_GD_EXTENSION_H
#define GODOT_GD_EXTENSION_H


#include "classes/ref.hpp"

void initialize_steele_module();
void uninitialize_steele_module();


namespace godot
{
	template<class T>
	class ByValWrap : public RefCounted
	{
	private:
		T value;
		
	public:
		~ByValWrap() override = default;
		ByValWrap() = default;
		
		ByValWrap(const T& t) : value(t) {}
		ByValWrap(T&& t) : value(std::move(t)) {}
		
		
	public:
		inline const T& get_steele_value() const { return value; }
		inline T& get_steele_value() { return value; }
		inline void set_steele_value(const T& t) { value = t; }
	};
	
	template<class T>
	inline Ref<T> ref(const T& t)
	{
		godot::Ref<T> r;
		
		r.instantiate();
		*r = t;
		
		return r;
	}
}


#endif