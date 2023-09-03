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


std::string Steele::RNG::XoroshiroRNG::Seed() const
{
	return m_seed;
}

bool Steele::RNG::XoroshiroRNG::NextBool()
{
	return NextUInt64() & 1;
}

char Steele::RNG::XoroshiroRNG::NextChar()
{
	return (char)NextUInt64();
}

char Steele::RNG::XoroshiroRNG::NextChar(char min, char max)
{
	return (char)NextInt64(min, max);
}

int Steele::RNG::XoroshiroRNG::NextInt()
{
	return (int)NextUInt64();
}

int Steele::RNG::XoroshiroRNG::NextInt(int min, int max)
{
	return (int)NextInt64(min, max);
}

int64_t Steele::RNG::XoroshiroRNG::NextInt64()
{
	return (int64_t)NextUInt64();
}

int64_t Steele::RNG::XoroshiroRNG::NextInt64(int64_t min, int64_t max)
{
	return 0;
}

uint64_t Steele::RNG::XoroshiroRNG::NextUInt64()
{
	return xoroshiro128plus_next(m_config, CurrentState());
}

uint64_t Steele::RNG::XoroshiroRNG::NextUInt64(uint64_t min, uint64_t max)
{
	if (max <= min) return min;
	
	auto diff = max - min + 1;
	auto maxGeneration = (UINT64_MAX / diff) * diff;
	
	auto num = NextUInt64();
	
	while (num > maxGeneration)
	{
		num = NextUInt64();
	}
	
	return min + (num % diff);
}

double Steele::RNG::XoroshiroRNG::NextDouble()
{
	return (double)((uint)NextInt()) / (double)UINT32_MAX;
}

double Steele::RNG::XoroshiroRNG::NextDouble(double min, double max)
{
	if (max <= min) return min;
	
	return min + (max - min) * NextDouble();
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