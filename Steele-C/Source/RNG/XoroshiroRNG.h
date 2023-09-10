#ifndef STEELE_XOROSHIRORNG_H
#define STEELE_XOROSHIRORNG_H


#include "IRNG.h"
#include "Algo/xoroshiro128plus.h"


namespace Steele::RNG
{
	class XoroshiroRNG : public IRNG
	{
	private:
		xoroshiro128plus_config m_config	= default_config;
		uint64_t				m_state[2]	= {1, 1 };
		std::string 			m_seed;
		
		
	private:
		uint64_t* CurrentState();
		
	private:
		static void Init(const xoroshiro128plus_config& config, uint64_t item[2]) noexcept;
		
	
	public:
		explicit XoroshiroRNG(std::string  seed);
		explicit XoroshiroRNG(const xoroshiro128plus_config& config);
		XoroshiroRNG(const xoroshiro128plus_config& config, std::string  seed);
		
		XoroshiroRNG& operator=(const XoroshiroRNG&) = default;
		XoroshiroRNG& operator=(XoroshiroRNG&&) = default;
		
		~XoroshiroRNG() = default;
		
		
	public:
		inline xoroshiro128plus_config GetConfig() { return m_config; }
		inline void SetConfig(const xoroshiro128plus_config& config) { m_config = config; }
		
	
	public:
		void SetState(const std::initializer_list<uint64_t>& state);
		void SetState(const uint64_t state[2]);
	
	
	public:
		std::string seed() const override;
		
		bool		next_bool() override;
		char		next_char() override;
		char		next_char(char min, char max) override;
		int			next_int_32() override;
		int			next_int_32(int min, int max) override;
		int64_t 	next_int_64() override;
		int64_t		next_int_64(int64_t min, int64_t max) override;
		uint64_t 	next_uint_64() override;
		uint64_t	next_uint_64(uint64_t min, uint64_t max) override;
		double		next_double() override;
		double		next_double(double min, double max) override;
	};
}

#endif