#include "XoroshiroRNG.h"

#include <utility>


#pragma clang diagnostic push
#pragma ide diagnostic ignored "NullDereference"
uint64_t Steele::XoroshiroRNG::StateCast::state_from_vector(const std::vector<byte>& source, int offset)
{
	for (int i = 0; i < sizeof(BYTES); i++)
	{
		if (source.size() <= offset + i)
			break;
		
		BYTES[i] = source[offset + i];
	}
	
	if (UINT == 0)
		UINT = 1;
	
	return UINT;
}
#pragma clang diagnostic pop

void Steele::XoroshiroRNG::StateCast::state_to_vector(uint64_t val, std::vector<byte>& source)
{
	UINT = val;
	
	for (byte b : BYTES)
	{
		source.push_back(b);
	}
}

void Steele::XoroshiroRNG::StateCast::from_string(const std::string& source, int offset)
{
	if (source.empty())
	{
		UINT = 0;
	}
	else
	{
		int size = (int)source.size();
		auto c_str = source.c_str();
		
		for (byte& i : BYTES)
		{
			i = (byte)c_str[offset++ % size];
		}
	}
}


void Steele::XoroshiroRNG::init()
{
	const int MIX_MIN				= 100;
	const int MIX_SCALE				= 5;
	const int MIX_RANGE_PER_STATE	= 10;
	
	m_stateIndex = 0;
	
	int mixStrength = std::max(MIX_MIN, (int)(m_state.size()) * MIX_SCALE);
	
	for (auto i = 0; i < mixStrength; i++)
	{
		auto mixCount = next_uint_64();
		
		mixCount = 1 + mixCount % MIX_RANGE_PER_STATE;
		
		for (auto mix = 0; mix < mixCount; mix++)
		{
			next_uint_64();
		}
	}
	
	m_stateIndex = 0;
}

std::vector<uint64_t> Steele::XoroshiroRNG::generate_state(
	const std::string& seed, 
	const std::vector<int32_t>& ref,
	StateReference::RefType	type)
{
	std::vector<uint64_t> result;
	StateCast primaryCast	= {};
	StateCast seedCast		= {};
	
	auto& primary = primaryCast.Primary;
	
	int seedIndex	= 0;
	int refIndex	= 0;
	auto refSize = ref.size();
	auto seedSize = seed.size();
	auto seedBits = (size_t)ceil((double)(seedSize) / (double)sizeof(StateCast));
	auto size = (size_t)std::max(
		(size_t)1, 
		std::max(refSize, seedBits));
	
	
	result.reserve(size);
	primary.RefType		= (byte)type;
	primary.RefValue	= { .Int32 = 0 };
	
	for (auto i = 0; i < size; i++)
	{
		primary.Index = i + 1;
		
		// Add reference value
		{
			if (refSize)
			{
				primary.RefValue.Int32 = ref[refIndex++ % refSize];
			}
		}
		// Add the seed
		{
			seedCast.from_string(seed, seedIndex);
			seedIndex += sizeof seedCast.BYTES;
		}
		// Set repeat index to the correct value if necessary
		{
			if (primary.RepeatIndex)
			{
				primary.RepeatIndex++;
			}
			else if (
				(seedBits && seedIndex > seedSize) ||  
				(refSize && refIndex > refSize))
			{
				primary.RepeatIndex = 1;
			}
		}
		
		result.push_back(primaryCast.UINT);
		result.push_back(seedCast.UINT);
	}
	
	return result;
}


uint64_t* Steele::XoroshiroRNG::current_state()
{
	uint64_t* curr = &m_state[m_stateIndex];
	m_stateIndex += 2;
	
	if (m_stateIndex >= m_state.size())
	{
		m_stateIndex = 0;
	}
	
	return curr;
}


Steele::XoroshiroRNG::XoroshiroRNG(std::string str) : 
	m_seed(std::move(str))
{
	XoroshiroRNG::reset_state(); 
}

Steele::XoroshiroRNG::XoroshiroRNG(const Steele::RandomState& state)
{
	XoroshiroRNG::reset_state(state);
}

Steele::XoroshiroRNG::XoroshiroRNG(std::string str, StateReference ref) : 
	m_ref(ref),
	m_seed(std::move(str))
{
	XoroshiroRNG::reset_state(); 
}

Steele::XoroshiroRNG::XoroshiroRNG(const std::string& str, int jump) : XoroshiroRNG(str)
{
	this->jump(jump);
}

Steele::XoroshiroRNG::XoroshiroRNG(const Steele::xoroshiro128plus_config &config) :
	m_config(config)
{
	
}


bool Steele::XoroshiroRNG::next_bool()
{
	return next_uint_64() & 1;
}

char Steele::XoroshiroRNG::next_char()
{
	return (char)next_uint_64();
}

char Steele::XoroshiroRNG::next_char(char min, char max)
{
	return (char)next_int_64(min, max);
}

int Steele::XoroshiroRNG::next_int_32()
{
	return (int)next_uint_64();
}

int Steele::XoroshiroRNG::next_int_32(int min, int max)
{
	return (int)next_int_64(min, max);
}

int64_t Steele::XoroshiroRNG::next_int_64()
{
	return (int64_t)next_uint_64();
}

int64_t Steele::XoroshiroRNG::next_int_64(int64_t min, int64_t max)
{
	int64_t diff = max - min;
	return min + (int64_t)next_uint_64(0, diff);
}

uint64_t Steele::XoroshiroRNG::next_uint_64()
{
	if (m_state.empty()) return 0;
	
	return xoroshiro128plus_next(m_config, current_state());
}

uint64_t Steele::XoroshiroRNG::next_uint_64(uint64_t min, uint64_t max)
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

double Steele::XoroshiroRNG::next_double()
{
	return (double)((uint) next_int_32()) / (double)UINT32_MAX;
}

double Steele::XoroshiroRNG::next_double(double min, double max)
{
	if (max <= min) return min;
	
	return min + (max - min) * next_double();
}


std::string Steele::XoroshiroRNG::get_seed() const
{
	return m_seed;
}

void Steele::XoroshiroRNG::reset_state(std::string seed)
{
	m_seed = seed;
	reset_state();
}

void Steele::XoroshiroRNG::reset_state(const Steele::RandomState& state)
{
	set_state(state);
	reset_state();
}

void Steele::XoroshiroRNG::reset_state()
{
	m_state = generate_state(m_seed, m_ref.to_vector(), m_ref.Type);
	init();
}

Steele::RandomState Steele::XoroshiroRNG::get_state() const
{
	RandomState r;
	get_state(r);
	return r;
}

void Steele::XoroshiroRNG::get_state(Steele::RandomState& target) const
{
	StateCast c;
	
	target.Reference = m_ref;
	target.Seed = m_seed;
	
	clear(target.State, 1 + m_state.size() * 8);
	
	target.State.push_back((byte)m_stateIndex);
	
	for (auto u : m_state)
	{
		c.state_to_vector(u, target.State);
	}
}

void Steele::XoroshiroRNG::set_state(const Steele::RandomState& state)
{
	m_seed	= state.Seed;
	m_ref	= state.Reference;
	
	StateCast c;
	auto v_state = state.State;
	
	remove_after_index(v_state, 255);
	
	clear(m_state);
	m_state.reserve((v_state.size() - 1) / 8);
	
	if (v_state.empty())
	{
		m_stateIndex = 0;
	}
	else
	{
		m_stateIndex = (int)(v_state[0]);
	}
	
	
	for (int i = 1; i < v_state.size(); i += 8)
	{
		auto val = c.state_from_vector(v_state, i);
		m_state.push_back(val);
	}
	
	
	while (m_state.empty() || m_state.size() % 2 == 1)
	{
		m_state.push_back(1);
	}
	
	if (m_stateIndex < 0 || m_stateIndex >= m_state.size())
	{
		m_stateIndex = 0;
	}
}


Steele::RandomState Steele::XoroshiroRNG::create_referenced_state(StateReference ref) const
{
	XoroshiroRNG state;
	
	state.m_ref = StateReference(ref);
	state.reset_state(m_seed);
	
	return state.get_state();
}

Steele::RandomState Steele::XoroshiroRNG::create_referenced_state(v2i ref) const
{
	return create_referenced_state(StateReference(ref));
}

Steele::RandomState Steele::XoroshiroRNG::create_referenced_state(v3i ref) const
{
	return create_referenced_state(StateReference(ref));
}

Steele::RandomState Steele::XoroshiroRNG::create_referenced_state(float ref) const
{
	return create_referenced_state(StateReference(ref));
}

Steele::RandomState Steele::XoroshiroRNG::create_referenced_state(int32_t ref) const
{
	return create_referenced_state(StateReference(ref));
}


void Steele::XoroshiroRNG::jump(int count)
{
	for (int i = 0; i < count; i++)
	{
		next_uint_64();
	}
}

Steele::StateReference Steele::XoroshiroRNG::get_reference() const
{
	return m_ref;
}
