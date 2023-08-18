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
		XoroshiroRNG(std::string  seed);
		XoroshiroRNG(const xoroshiro128plus_config& config);
		XoroshiroRNG(const xoroshiro128plus_config& config, std::string  seed);
		
		~XoroshiroRNG() = default;
		
		
	public:
		inline xoroshiro128plus_config GetConfig() { return m_config; }
		inline void SetConfig(const xoroshiro128plus_config& config) { m_config = config; }
		
	
	public:
		void SetState(const uint64_t state[2]);
	
	
	public:
		sptr<void*> GetState() const override;
		void SetState(sptr<void*> state) override;
		std::string Seed() const override;
		
		bool		NextBool() override;
		char		NextChar() override;
		char		NextChar(char min, char max) override;
		int			NextInt() override;
		int			NextInt(int min, int max) override;
		int64_t 	NextInt64() override;
		int64_t		NextInt64(int64_t min, int64_t max) override;
		uint64_t 	NextUInt64() override;
		uint64_t	NextUInt64(uint64_t min, uint64_t max) override;
		double		NextDouble() override;
		double		NextDouble(double min, double max) override;
	};
}

#endif