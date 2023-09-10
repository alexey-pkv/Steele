#include "XoroshiroRNG.h"

#include <utility>


void Steele::RNG::XoroshiroRNG::Init(const xoroshiro128plus_config& config, uint64_t* item) noexcept
{
	for (auto i = 0; i < 5; i++)
	{
		xoroshiro128plus_next(config, item);
	}
}


Steele::RNG::XoroshiroRNG::XoroshiroRNG(std::string seed) : 
	m_seed(std::move(seed))
{
	
}

Steele::RNG::XoroshiroRNG::XoroshiroRNG(const Steele::RNG::xoroshiro128plus_config &config) :
	m_config(config)
{
	
}

Steele::RNG::XoroshiroRNG::XoroshiroRNG(const Steele::RNG::xoroshiro128plus_config &config, std::string seed) :
	m_seed(std::move(seed)),
	m_config(config)
{
	
}


std::string Steele::RNG::XoroshiroRNG::seed() const
{
	return m_seed;
}

bool Steele::RNG::XoroshiroRNG::next_bool()
{
	return next_uint_64() & 1;
}

char Steele::RNG::XoroshiroRNG::next_char()
{
	return (char) next_uint_64();
}

char Steele::RNG::XoroshiroRNG::next_char(char min, char max)
{
	return (char) next_int_64(min, max);
}

int Steele::RNG::XoroshiroRNG::next_int_32()
{
	return (int) next_uint_64();
}

int Steele::RNG::XoroshiroRNG::next_int_32(int min, int max)
{
	return (int) next_int_64(min, max);
}

int64_t Steele::RNG::XoroshiroRNG::next_int_64()
{
	return (int64_t) next_uint_64();
}

int64_t Steele::RNG::XoroshiroRNG::next_int_64(int64_t min, int64_t max)
{
	return 0;
}

uint64_t Steele::RNG::XoroshiroRNG::next_uint_64()
{
	return xoroshiro128plus_next(m_config, CurrentState());
}

uint64_t Steele::RNG::XoroshiroRNG::next_uint_64(uint64_t min, uint64_t max)
{
	if (max <= min) return min;
	
	auto diff = max - min + 1;
	auto maxGeneration = (UINT64_MAX / diff) * diff;
	
	auto num = next_uint_64();
	
	while (num > maxGeneration)
	{
		num = next_uint_64();
	}
	
	return min + (num % diff);
}

double Steele::RNG::XoroshiroRNG::next_double()
{
	return (double)((uint) next_int_32()) / (double)UINT32_MAX;
}

double Steele::RNG::XoroshiroRNG::next_double(double min, double max)
{
	if (max <= min) return min;
	
	return min + (max - min) * next_double();
}


uint64_t* Steele::RNG::XoroshiroRNG::CurrentState()
{
	return m_state;
}

void Steele::RNG::XoroshiroRNG::SetState(const std::initializer_list<uint64_t>& state)
{
	m_state[0] = *state.begin();
	m_state[1] = *(state.begin() + 1);
	
	Init(m_config, m_state);
}

void Steele::RNG::XoroshiroRNG::SetState(const uint64_t* state)
{
	m_state[0] = state[0];
	m_state[1] = state[1];
	
	Init(m_config, m_state);
}