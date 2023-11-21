#ifndef STEELE_PALETTES_H
#define STEELE_PALETTES_H


#include "Base/RNG/IRNG.h"
#include "DataTypes/Types.h"


namespace Steele
{
	template<typename T>
	class IScalarContainer
	{
	public:
		virtual float total_weight() const = 0;
		virtual size_t size() const = 0;
		virtual bool is_empty() const = 0;
		virtual bool has(const T& t) const = 0;
		virtual float weight(const T& t) const = 0;
		virtual void add(const T& t) = 0;
		virtual void add(const T& t, float weight) = 0;
		virtual bool remove(const T& t) = 0;
	};
	
	template<typename T>
	class IScalarSelect
	{
	public:
		virtual T select_random(IRNG& rng) const = 0;
	};
	
	
	template<typename T>
	class ScalarPalette : public IScalarContainer<T>
	{
	private:
		std::map<T, float>	m_palette;
		float				m_totalWeight = 0;
		
		
	protected:
		std::map<T, float>& palette() { return m_palette; }
		const std::map<T, float>& palette() const { return m_palette; }
		
		
	public:
		virtual ~ScalarPalette() = default;
		
		ScalarPalette() = default;
		ScalarPalette(const ScalarPalette& s) = default;
		ScalarPalette(ScalarPalette&& s) noexcept = default;
		
		ScalarPalette& operator=(const ScalarPalette&) = default;
		ScalarPalette& operator=(ScalarPalette&&) = default;
		
		
	public:
		float total_weight() const override { return m_totalWeight; }
		size_t size() const override { return m_palette.size(); }
		bool is_empty() const override { return m_palette.empty(); }
		bool has(const T& t) const override { return m_palette.find(t) != m_palette.end(); }
		
		float weight(const T& t) const override 
		{
			auto res = m_palette.find(t);
			
			if (res == m_palette.end())
				return 0;
			
			return res->second;
		}
		
		void add(const T& t) override
		{
			add(t, 1);
		}
		
		void add(const T& t, float weight) override
		{
			remove(t);
			
			m_totalWeight += weight;
			m_palette[t] = weight;
		} 
		
		bool remove(const T& t) override
		{
			auto res = m_palette.find(t);
			
			if (res == m_palette.end())
				return false;
			
			m_totalWeight -= res->second;
			m_palette.erase(res);
			
			return true;
		}
	};
	
	template<typename T>
	class ScalarSelectPalette : public ScalarPalette<T>, public IScalarSelect<T>
	{
	public:
		~ScalarSelectPalette() override = default;
		
		ScalarSelectPalette() = default;
		ScalarSelectPalette(const ScalarSelectPalette& s) = default;
		ScalarSelectPalette(ScalarSelectPalette&& s) noexcept = default;
		ScalarSelectPalette& operator=(const ScalarSelectPalette&) = default;
		ScalarSelectPalette& operator=(ScalarSelectPalette&&) = default;
		
		
	public:
		T select_random(IRNG& rng) const override
		{
			auto weight = this->total_weight() ;
			
			if (weight <= 0)
				return STEELE_NULL_ID;
			
			auto rnd = rng.next_double(0, weight);
			
			for (const auto& kvp : this->palette())
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
			
			return this->palette().rbegin()->first;
		}
	};
	
	class GenericIDPalette : public ScalarSelectPalette<t_id> {};
}


#endif
