#include "outline_scalar_iterator.h"


using namespace Steele;
using namespace Steele::Align;


outline_scalar_iterator::outline_scalar_iterator(const Area::outline_iterator& outline, bool isX):
	m_outline(outline),
	m_isXAxis(isX)
{
	
}

outline_scalar_iterator_provider::outline_scalar_iterator_provider(const Area::outline_iterator_provider& provider, Axis axis):
	m_provider(provider),
	m_isXAxis(axis == Axis::X)
{
	
}
