#ifndef STEELE_IRNG_H
#define STEELE_IRNG_H


#include <string>
#include <vector>

#include "../Utils.h"


namespace Steele::RNG
{
	class IRNG
	{
	public:
		virtual sptr<void*> GetState() const = 0;
		virtual void SetState(sptr<void*> state) = 0;
		
		virtual std::string Seed() const = 0;
		
		virtual bool		NextBool() = 0;
		
		virtual char		NextChar() = 0;
		virtual char		NextChar(char min, char max) = 0;
		
		virtual int			NextInt() = 0;
		virtual int			NextInt(int min, int max) = 0;
		
		virtual int64_t		NextInt64() = 0;
		virtual int64_t		NextInt64(int64_t min, int64_t max) = 0;
		
		virtual uint64_t	NextUInt64() = 0;
		virtual uint64_t	NextUInt64(uint64_t min, uint64_t max) = 0;
		
		virtual double	NextDouble() = 0;
		virtual double	NextDouble(double min, double max) = 0;
		
		
		template<typename T>
		inline T NextElement(std::vector<T> v, const T& def) 
		{
			if (v.empty())
				return def;
			
			return v[NextInt(0, v.size() - 1)];
		}
		template<typename K, typename V>
		inline V& NextElement(const std::map<K, V>& map) 
		{
			int next = NextInt(0, map.size() - 1);
			return (map.begin())->second;
		}
	};
}


#endif