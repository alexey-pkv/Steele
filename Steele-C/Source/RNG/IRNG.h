#ifndef STEELE_IRNG_H
#define STEELE_IRNG_H


#include <string>
#include <vector>

#include "../Utils.h"
#include "Exceptions/SteeleException.h"


namespace Steele::RNG
{
	class IRNG
	{
	public:
		virtual std::string seed() const = 0;
		
		virtual bool		next_bool() = 0;
		
		virtual char		next_char() = 0;
		virtual char		next_char(char min, char max) = 0;
		
		virtual int			next_int_32() = 0;
		virtual int			next_int_32(int min, int max) = 0;
		
		virtual int64_t		next_int_64() = 0;
		virtual int64_t		next_int_64(int64_t min, int64_t max) = 0;
		
		virtual uint64_t	next_uint_64() = 0;
		virtual uint64_t	next_uint_64(uint64_t min, uint64_t max) = 0;
		
		virtual double	next_double() = 0;
		virtual double	next_double(double min, double max) = 0;
		
		
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
		template<typename T> T next();
		template<typename T> T next(T min, T max);
		template<typename K, typename V> inline V& next_element(const std::map<K, V>& map);
#pragma clang diagnostic pop
		
		
		template<typename T>
		inline T next_element(std::vector<T> v, const T& def) 
		{
			if (v.empty())
				return def;
			
			return v[next_int_32(0, v.size() - 1)];
		}
		
		template<typename T>
		inline int next_index(const T* v, int size) 
		{
			if (size <= 0)
				return 0;
			
			T total = 0;
			
			for (auto i = 0; i < size; i++)
			{
				total += v[i];
			}
			
			if (total == 0)
				return 0;
			
			auto rnd = next<T>((float) 0, total);
			
			for (auto i = 0; i < size; i++)
			{
				if (rnd <= v[i])
					return i;
				
				rnd -= v[i];
			}
			
			return size - 1;
		}
		
	};
}


#endif