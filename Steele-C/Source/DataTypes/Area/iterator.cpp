#include "../Area.h"


using namespace Steele;


void Area::iterator::operator++()
{
	Inner++;
	
	while (Inner == InnerEnd)
	{
		Primary++;
		Index++;
		
		if (Primary != PrimaryEnd)
		{
			Inner = Primary->begin();
			InnerEnd = Primary->end();
		}
		else
		{
			Inner = {};
			InnerEnd = {};
			
			break;
		}
	}
}

Area::iterator Area::begin() const
{
	if (m_vertical.empty())
	{
		return {
			.Primary = m_vertical.begin(),
			.PrimaryEnd = m_vertical.end()
		};
	}
	else
	{
		auto primary = m_vertical.begin();
		
		return {
			.XOffset	= m_offset.x,
			.Inner		= primary->begin(),
			.InnerEnd	= primary->end(),
			.Primary	= primary,
			.PrimaryEnd = m_vertical.end()
		};
	}
}

Area::iterator Area::end() const
{
	return {
		.XOffset	= m_offset.x,
		.Index		= (int)m_vertical.size(),
		.Primary	= m_vertical.end(),
		.PrimaryEnd	= m_vertical.end()
	};
}


v2i Area::outline_iterator::operator*() const
{
	const auto& item = Source[Index];
	
	switch ((int)Style)
	{
		case IterationStyle::TOP:
			return {Offset, item.max() };
		case IterationStyle::BOTTOM:
			return { Offset, item.min() };
		case IterationStyle::LEFT:
			return {item.min(), Offset };
		case IterationStyle::RIGHT:
			return {item.max(), Offset };
		default:
			return {};
	}
}

Area::outline_iterator::outline_iterator(const vector<AreaLine>& source, int offset, int direction, int index, IterationStyle style) : 
	Source(source),
	Offset(offset + index),
	Direction(direction),
	Index(index),
	Style(style)
{
	
}

Area::outline_iterator_provider::outline_iterator_provider(const vector<AreaLine>& v, int offset, Area::outline_iterator::IterationStyle style, bool isReverse):
	m_lines(v), m_offset(offset), m_style(style), m_direction(isReverse ? -1 : 1)
{
	
}