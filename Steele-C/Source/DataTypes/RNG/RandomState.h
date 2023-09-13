#ifndef STEELE_RANDOMSTATE_H
#define STEELE_RANDOMSTATE_H


#include <string>
#include <vector>

#include "DataTypes/Types.h"
#include "ReferenceValue.h"


namespace Steele
{
	struct RandomState
	{
	public:
		~RandomState() = default;
		
		RandomState() = default;
		RandomState(const RandomState&) = default;
		RandomState(RandomState&&) = default;
		
		RandomState& operator=(const RandomState&) = default;
		RandomState& operator=(RandomState&&) = default;
		
	public:
		std::string			Seed;
		std::vector<::byte>	State		= {};
		ReferenceValue		Reference;
		
		
	public:
		inline bool has_reference() const { return Reference.has_reference(); }
		inline void remove_reference() { Reference.remove_reference(); }
		
		inline void set_reference(const v3i& ref)	{ Reference.set_reference(ref); }
		inline void set_reference(const v2i& ref)	{ Reference.set_reference(ref); }
		inline void set_reference(int32_t ref)		{ Reference.set_reference(ref); }
		inline void set_reference(float ref)		{ Reference.set_reference(ref); }
	};
}


#endif