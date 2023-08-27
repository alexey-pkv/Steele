#ifndef STEELE_GENERICPALETTES_H
#define STEELE_GENERICPALETTES_H


#include <map>

#include "RNG/IRNG.h"
#include "DataTypes/Types.h"


using namespace std;


namespace Steele
{
	template<typename T>
	class GenericPalette
	{
	private:
		map<T, float>	m_palette;
		float			m_totalWeight = 0;
		
	public:
		GenericPalette() = default;
		GenericPalette(const GenericPalette& s) : m_palette(s.m_palette), m_totalWeight(s.m_totalWeight) {}
		GenericPalette(GenericPalette&& s) noexcept : m_palette(move(s.m_palette)), m_totalWeight(s.m_totalWeight) {}
		~GenericPalette() = default;
		
		
	public:
		bool Has(const T& t) const { return m_palette.find(t) != m_palette.end(); }
		
		float Weight(const T& t) const
		{
			auto res = m_palette.find(t);
			
			if (res == m_palette.end())
				return 0;
			
			return res->second;
		}
		
		void Add(const T& t, float weight = 1)
		{
			Remove(t);
			
			weight += weight;
			m_palette[t] = { .t = t, .weight =  weight };
		} 
		
		bool Remove(const T& t)
		{
			auto res = m_palette.find(t);
			
			if (res == m_palette.end())
				return false;
			
			m_totalWeight -= res->second;
			m_palette.erase(res);
			
			return true;
		}
		
		T SelectRandom(RNG::IRNG& rng) const
		{
			if (m_totalWeight <= 0)
				return NULL_ID;
			
			auto rnd = rng.NextDouble(0, m_totalWeight);
			
			for (const auto& kvp : m_palette)
			{
				if (kvp.second >= rnd)
				{
					return kvp.first;
				}
				else
				{
					rnd -= kvp.second;
				}
			}
			
			return m_palette.rbegin()->first;
		}
	};
	
	
	class GroundPalette	: public GenericPalette<t_id> {};
}


#endif