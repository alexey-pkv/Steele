#include "../Area.h"
#include "Utils.h"


using namespace Steele;


Area::AreaLine::AreaLine(v2i v)
	: m_line({v})
{
	
}


bool Area::AreaLine::contains(int y) const
{
	for (auto v : m_line)
	{
		if (y < v.x) 
			return false;
		else if (y <= v.y)
			return true;
	}
	
	return false;
}

bool Area::AreaLine::contains(const v2i &v) const
{
	for (auto n : m_line)
	{
		if (v.y < n.x) 
			return false;
		else if (n.x <= v.x && v.y <= n.y)
			return true;
	}
	
	return false;
}

bool Area::AreaLine::contains(const AreaLine &yva) const
{
	for (auto n : yva.m_line)
	{
		if (!contains(n))
		{
			return false;
		}
	}
	
	return true;
}

bool Area::AreaLine::overlaps(const v2i& v) const
{
	for (auto& n : m_line)
	{
		if (n.x > v.y)
			return false;
		if (v.x <= n.y)
			return true;
	}
	
	return false;
}

bool Area::AreaLine::overlaps(const AreaLine &yva) const
{
	for (auto& n : yva.m_line)
	{
		if (overlaps(n))
		{
			return true;
		}
	}
	
	return false;
}

void Area::AreaLine::flip(int offset)
{
	if (is_empty())
		return;
	
	for (auto& v : m_line)
	{
		auto t = v.x;
		v.x = offset - v.y;
		v.y = offset - t;
	}
	
	reverse(m_line);
}

uint64_t Area::AreaLine::area() const
{
	uint64_t area = 0;
	
	for (auto v : m_line)
	{
		area += v.y - v.x + 1; 
	}
	
	return area;
}

bool Area::AreaLine::is_empty() const
{
	return m_line.empty();
}

int Area::AreaLine::min() const
{
	return is_empty() ? 0 : m_line.front().x;
}

int Area::AreaLine::max() const
{
	return is_empty() ? 0 : m_line.back().y;
}

void Area::AreaLine::clear()
{
	m_line.clear();
}


void Area::AreaLine::operator|=(const AreaLine &yva)
{
	if (yva.is_empty())
	{
		return;
	}
	else if (is_empty()) 
	{
		m_line = yva.m_line;
		return;
	}
	
	vector<v2i> result;
	auto a_curr = m_line.begin();
	auto b_curr	= yva.m_line.begin();
	
	v2i curr = (a_curr->x < b_curr->x ? *a_curr : *b_curr);
	
	while (a_curr != m_line.end() || b_curr != yva.m_line.end())
	{
		v2i curr_compare;
		
		if (b_curr == yva.m_line.end())
		{
			curr_compare = *a_curr;
			a_curr++;
		}
		else if (a_curr == m_line.end())
		{
			curr_compare = *b_curr;
			b_curr++;
		}
		else if (a_curr->x < b_curr->x)
		{
			curr_compare = *a_curr;
			a_curr++;
		}
		else // if (b_curr->x <= a_curr->x)
		{
			curr_compare = *b_curr;
			b_curr++;
		}
		
		if (curr.y < curr_compare.x - 1)
		{
			result.emplace_back(curr);
			curr = curr_compare;
		}
		else
		{
			curr.y = ::max(curr_compare.y, curr.y);
		}
	}
	
	result.emplace_back(curr);
	
	m_line = result;
}

void Area::AreaLine::operator-=(const AreaLine &yva)
{
	if (is_empty() || yva.is_empty()) return;
	
	vector<v2i> result;
	
	auto a_curr = m_line.begin();
	auto a_end = m_line.end();
	auto b_curr	= yva.m_line.begin();
	auto b_end = yva.m_line.end();
	
	while (a_curr != a_end && b_curr != b_end)
	{
		// curr:          [...           
		// b:      ...]
		if (b_curr->y < a_curr->x)
		{
			b_curr++;
			continue;
		}
		
		// curr:    [##]....           
		// b:           [...
		if (b_curr->x > a_curr->x)
		{
			result.push_back({ a_curr->x, ::min(b_curr->x - 1, a_curr->y) });
		}
		
		// curr:    ...]          
		// b:     .........]
		if (b_curr->y >= a_curr->y)
		{
			a_curr++;
		}
		// curr:    [...          [###]           
		// b:     .......        ]
		else
		{
			a_curr->x = b_curr->y + 1;
			b_curr++;
		}
	}
	
	if (a_curr != a_end)
	{
		result.insert(result.end(), a_curr, a_end);
	}
	
	m_line = result;
}

void Area::AreaLine::operator&=(int with)
{
	bool found = false;
	
	if (is_empty())
		return;
	
	for (auto v : m_line)
	{
		if (with <= v.y)
		{
			found = with >= v.x;
		}
	}
	
	if (found)
	{
		auto& first = m_line[0];
		
		first.x = with;
		first.y = with;
		
		m_line.erase(m_line.begin() + 1, m_line.end());
	}
	else
	{
		m_line.clear();
	}
}

void Area::AreaLine::operator&=(const AreaLine &yva)
{
	vector<v2i> result;
	
	auto a_curr = m_line.begin();
	auto b_curr	= yva.m_line.begin();
	
	while (a_curr != m_line.end() && b_curr != yva.m_line.end())
	{
		if (b_curr->x <= a_curr->y && a_curr->x <= b_curr->y)
		{
			result.emplace_back( 
				::max(a_curr->x, b_curr->x),
				::min(a_curr->y, b_curr->y)
			);
		}
		
		if (a_curr->y < b_curr->y)
		{
			a_curr++;
		}
		else
		{
			b_curr++;
		}
	}
	
	m_line = result;
}

bool Area::AreaLine::operator&&(const Area::AreaLine &yva) const
{
	vector<v2i> result;
	
	auto a_curr = m_line.begin();
	auto b_curr	= yva.m_line.begin();
	
	while (a_curr != m_line.end() && b_curr != yva.m_line.end())
	{
		if (b_curr->x <= a_curr->y && a_curr->x <= b_curr->y)
		{
			return true;
		}
		
		if (a_curr->y < b_curr->y)
		{
			a_curr++;
		}
		else
		{
			b_curr++;
		}
	}
	
	return false;
}

void Area::AreaLine::operator>>=(int by)
{
	for (auto& v : m_line)
	{
		v.x += by;
		v.y += by;
	}
}

void Area::AreaLine::operator<<=(int by)
{
	for (auto& v : m_line)
	{
		v.x -= by;
		v.y -= by;
	}
}


Area::AreaLine::Iterator Area::AreaLine::begin() const
{
	int val = 0;
	auto begin = m_line.begin();
	auto end = m_line.end();
	
	if (!m_line.empty())
	{
		 val = begin->x; 
	}
	
	return { 
		.CurrCoord	= val,
		.CurrIndex	= begin,
		.End		= end
	};
}

Area::AreaLine::Iterator Area::AreaLine::end() const
{
	int val = 0;
	auto begin = m_line.begin();
	auto end = m_line.end();
	
	if (!m_line.empty())
	{
		 val = m_line.back().y + 1;
	}
	
	return { 
		.CurrCoord	= val,
		.CurrIndex	= begin,
		.End		= end
	};
}

void Area::AreaLine::Iterator::operator++(int)
{
	CurrCoord++;
	
	if (CurrCoord > CurrIndex->y)
	{
		CurrIndex++;
		
		if (CurrIndex != End)
		{
			CurrCoord = CurrIndex->x;
		}
	}
}