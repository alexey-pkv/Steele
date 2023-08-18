#ifndef STEELE_OUTLINE_SCALAR_ITERATOR_H
#define STEELE_OUTLINE_SCALAR_ITERATOR_H


#include "DataTypes/Area.h"


namespace Steele::Align
{
	struct outline_scalar_iterator
	{
	private:
		Area::outline_iterator m_outline;
		bool m_isXAxis;
		
		
	public:
		outline_scalar_iterator(const Area::outline_iterator& outline, bool isX);
		
		~outline_scalar_iterator() = default;
		outline_scalar_iterator(const outline_scalar_iterator&) = default;
		outline_scalar_iterator(outline_scalar_iterator&&) = default;
		
		
	public:
		inline bool operator!=(const outline_scalar_iterator& to) const { return to.m_outline != m_outline; }
		inline bool operator==(const outline_scalar_iterator& to) const { return to.m_outline == m_outline; }
		inline int operator*() const { return m_isXAxis ? (*m_outline).x : (*m_outline).y; }
		inline void operator++(int) { m_outline++; }
	};
	
	
	
	struct outline_scalar_iterator_provider
	{
	private:
		Area::outline_iterator_provider m_provider;
		bool m_isXAxis;
		
		
	public:
		outline_scalar_iterator_provider(Area::outline_iterator_provider provider, bool isX);
		
		~outline_scalar_iterator_provider() = default;
		outline_scalar_iterator_provider(const outline_scalar_iterator_provider&) = default;
		outline_scalar_iterator_provider(outline_scalar_iterator_provider&&) = default;
		
		
	public:
		inline outline_scalar_iterator begin() const { return { m_provider.begin(), m_isXAxis }; }
		inline outline_scalar_iterator end() const { return { m_provider.end(), m_isXAxis }; }
	};
}


#endif