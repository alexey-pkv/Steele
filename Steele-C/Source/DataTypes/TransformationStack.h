#ifndef STEELE_TRANSFORMATIONSTACK_H
#define STEELE_TRANSFORMATIONSTACK_H


#include <stack>
#include "Transformation.h"
#include "Types.h"


using namespace std;


namespace Steele
{
	class TransformationStack
	{
	private:
		stack<Transformation>	m_stack;
		Transformation			m_current;
		
		
	public:
		bool Pop();
		void Push(const Transformation& t);
		
	
	public:
		inline Transformation Top() const { return m_stack.empty() ? Transformation() : m_stack.top(); }
		inline const Transformation& Current() const { return m_current; }
	};
	
	
	static inline godot::Vector3i operator*(const v3i& v, const TransformationStack& ts) { return v * ts.Current(); }
	static inline void operator*=(v3i& v, const TransformationStack& ts) { v = v * ts; }
}


#endif