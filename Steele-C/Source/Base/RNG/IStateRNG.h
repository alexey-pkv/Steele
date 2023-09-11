#ifndef STEELE_STATERNG_H
#define STEELE_STATERNG_H


#include "DataTypes/RNG/RandomState.h"


namespace Steele
{
	class IStateRNG
	{
	public:
		virtual std::string	get_seed() const = 0;
		
		virtual void reset_state(std::string seed) = 0;
		virtual void reset_state(const RandomState& state) = 0;
		virtual void reset_state() = 0;
		
		virtual StateReference get_reference() const = 0;
		virtual RandomState get_state() const = 0;
		virtual void get_state(RandomState& target) const = 0;
		virtual void set_state(const RandomState& state) = 0;
		
		
	public:
		virtual RandomState create_referenced_state(v2i ref) const = 0;
		virtual RandomState create_referenced_state(v3i ref) const = 0;
		virtual RandomState create_referenced_state(float ref) const = 0;
		virtual RandomState create_referenced_state(int32_t ref) const = 0;
	};
}


#endif