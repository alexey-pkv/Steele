#ifndef STEELE_TRANSFORMATIONSTACK_H
#define STEELE_TRANSFORMATIONSTACK_H


#include <stack>

#include "DataTypes/Types.h"
#include "DataTypes/Transformation.h"


using namespace std;


namespace Steele
{
	class TransformationStack
	{
	private:
		stack<Transformation>	m_stack;
		Transformation			m_current;
		
		
	public:
		bool pop();
		void push(const Transformation& t);
		
	
	public:
		inline void clear() { stack<Transformation> empty; swap(m_stack, empty); m_current = {}; }
		inline size_t size() const { return m_stack.size(); }
		inline Transformation top() const { return m_stack.empty() ? Transformation() : m_stack.top(); }
		inline const Transformation& current() const { return m_current; }
	};
	
	
	static inline v3i operator*(const v3i& v, const TransformationStack& ts) { return v * ts.current(); }
	static inline void operator*=(v3i& v, const TransformationStack& ts) { v = v * ts; }
}


#endif