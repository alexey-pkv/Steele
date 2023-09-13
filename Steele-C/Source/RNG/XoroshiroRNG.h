#ifndef STEELE_XOROSHIRORNG_H
#define STEELE_XOROSHIRORNG_H


#include "Base/RNG/IRNG.h"
#include "Base/RNG/IStateRNG.h"

#include "Algo/xoroshiro128plus.h"


namespace Steele
{
	class XoroshiroRNG : public IRNG, public IStateRNG
	{
	private:
		struct StatePrimary
		{
		public:
			::byte Index;
			::byte RefType;
			::byte RepeatIndex	= 0;
			::byte EMPTY		= 0;
			
			union
			{
				int32_t Int32;
				float 	Float;
				::byte	Bytes[4];
				char	C_Str[4];
			} RefValue = { .Int32 = 0 };
		};
		
		union StateCast
		{
		private:
			
			
		public:
			uint64_t		UINT;
			::byte			BYTES[8];
			StatePrimary	Primary = {};
		
			
		public:
			void from_string(const std::string& source, int offset);
			
			
		public:
			uint64_t state_from_vector(const std::vector<::byte>& source, int offset);
			void state_to_vector(uint64_t val, std::vector<::byte>& source);
		};
		
		
		static_assert(sizeof(uint64_t) == sizeof(::byte) * 8);
		static_assert(sizeof(uint64_t) == sizeof(StatePrimary));
		static_assert(sizeof(uint64_t) == sizeof(StateCast));
		
		
		
	private:
		xoroshiro128plus_config m_config	= default_config;
		
		std::string 			m_seed;
		ReferenceValue			m_ref			= {};
		std::vector<uint64_t>	m_state			= { 1, 1 };
		int 					m_stateIndex	= 0;
		
		
	private:
		uint64_t* current_state();
		
	
	private:
		void init();
		static std::vector<uint64_t> generate_state(
				const std::string& seed,
				const std::vector<int32_t>& ref,
				ReferenceValue::RefType	type);
		
	
	public:
		explicit XoroshiroRNG() = default;
		explicit XoroshiroRNG(std::string str);
		explicit XoroshiroRNG(const RandomState& state);
		explicit XoroshiroRNG(std::string str, ReferenceValue ref);
		explicit XoroshiroRNG(const xoroshiro128plus_config& config);
		
		XoroshiroRNG(const std::string& str, int jump);
		
		XoroshiroRNG& operator=(const XoroshiroRNG&) = default;
		XoroshiroRNG& operator=(XoroshiroRNG&&) = default;
		
		~XoroshiroRNG() = default;
		
		
	public:
		inline xoroshiro128plus_config get_config() { return m_config; }
		inline void set_config(const xoroshiro128plus_config& config) { m_config = config; }
	
	
	public: // IRNG
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
		
		
	public: // IStateRNG
		std::string	get_seed() const override;
		
		void reset_state(std::string seed) override;
		void reset_state(const RandomState& state) override;
		void reset_state() override;
		
		ReferenceValue get_reference() const override;
		
		RandomState get_state() const override;
		void get_state(RandomState& target) const override;
		void set_state(const RandomState& state) override;
		
		
		RandomState create_referenced_state(v2i ref) const override;
		RandomState create_referenced_state(v3i ref) const override;
		RandomState create_referenced_state(float ref) const override;
		RandomState create_referenced_state(int32_t ref) const override;
		
		
	public:
		void jump(int count);
		RandomState create_referenced_state(ReferenceValue ref) const;
	};
}

#endif