#include "xoroshiro128plus.h"


uint64_t Steele::RNG::xoroshiro128plus_rotl(uint64_t x, int k) noexcept
{
	return (x << k) | (x >> (64 - k));
}

uint64_t Steele::RNG::xoroshiro128plus_next(const Steele::RNG::xoroshiro128plus_config &setup, uint64_t* state) noexcept
{
	uint64_t s0 = state[0];
	uint64_t s1 = state[1];
	
	uint64_t result = s0 + s1;

	s1 ^= s0;
	
	state[0] = Steele::RNG::xoroshiro128plus_rotl(s0, setup.A) ^ s1 ^ (s1 << setup.B);
	state[1] = Steele::RNG::xoroshiro128plus_rotl(s1, setup.C);

	return result;
}