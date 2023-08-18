#ifndef STEELE_RNG_XOROSHIRO128PLUS_H
#define STEELE_RNG_XOROSHIRO128PLUS_H


#include <cstdint>


namespace Steele::RNG
{
	/**
	 * @see https://prng.di.unimi.it/xoroshiro128plus.c
	 */
	
	struct xoroshiro128plus_config
	{
	public:
		int	A;
		int	B;
		int	C;
	};
	
	const struct xoroshiro128plus_config default_config = { .A = 24, .B = 16, .C = 37 };
	
	
	uint64_t xoroshiro128plus_rotl(uint64_t x, int k) noexcept;
	uint64_t xoroshiro128plus_next(const xoroshiro128plus_config& setup, uint64_t state[2]) noexcept;
	
	
	inline uint64_t xoroshiro128plus_next(uint64_t state[2]) noexcept { return xoroshiro128plus_next(default_config, state); }
}


#endif