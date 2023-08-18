#include <set>
#include <string>
#include <sstream>
#include <algorithm>


#include "Area.h"
#include "Types.h"
#include "Utils.h"
#include "Area/Alignment.h"


using namespace std;
using namespace Steele;


Area::Area(Rect2i r) : 
	m_offset(r.position)
{
	auto& size = r.size;
	
	if (size.x <= 0 || size.y <= 0)
	{
		m_offset = v2i_zero;
		return;
	}
	
	m_vertical.assign(size.x, AreaLine({ m_offset.y, m_offset.y + size.y - 1 }));
	m_horizontal.assign(size.y, AreaLine({ m_offset.x, m_offset.x + size.x - 1 }));
}

Area::Area(int x, int y, int to_x, int to_y) : 
	m_offset(x, y)
{
	if (to_x < x || to_y < y)
	{
		m_offset = v2i_zero;
		return;
	}
	
	m_vertical.assign(		to_x - x + 1, AreaLine({ y, to_y }));
	m_horizontal.assign(	to_y - y + 1, AreaLine({ x, to_x }));
}

Area::Area(int at_x, int at_y) : Area(at_x, at_y, at_x, at_y)
{
	
}

Area::Area(const std::string& area_template)
{
	auto lines = (int)std::count(area_template.begin(), area_template.end(), '\n');
	
	int x = 0;
	int y = lines - 1;
	
	for (auto c : area_template)
	{
		if (c == '.')
		{
			x++;
			continue;
		}
		else if (c == '\n')
		{
			y--;
			x = 0;
		}
		else if (c == '*')
		{
			*this |= Area(x, y);
			x++;
		}
	}
}


void Area::Clear()
{
	m_vertical.clear();
	m_horizontal.clear();
	m_offset = v2i_zero;
}

void Area::CleanUp()
{
	m_offset.x += CleanUp(m_vertical);
	
	if (m_vertical.empty())
	{
		m_horizontal.clear();
		m_offset = v2i_zero;
	}
	else
	{
		m_offset.y += CleanUp(m_horizontal);
	}
}

void Area::OffsetAll(vector<AreaLine> &lines, int by)
{
	if (by == 0) return;
	
	for (auto& line : lines)
	{
		line >>= by;
	}
}

void Area::FlipLines(vector<AreaLine>& lines, int offset)
{
	for (auto& n : lines)
	{
		n.Flip(offset);
	}
}

Area &Area::operator+=(const Vector2i &v)
{
	if (IsEmpty()) return *this;
	
	m_offset += v;
	
	if (v.x != 0)
	{
		OffsetAll(m_horizontal, v.x);
	}
	
	if (v.y != 0)
	{
		OffsetAll(m_vertical, v.y);
	}
	
	return *this;
}

Area& Area::operator*=(Direction dir)
{
	if (dir == Direction::North) return *this;
	
	auto offset = m_offset;
	
	ResetOffset();
	
	if (dir == Direction::East)
	{
		reverse(m_vertical);
		FlipLines(m_horizontal, Width() - 1);
		
		m_vertical.swap(m_horizontal);
	}
	else if (dir == Direction::South)
	{
		reverse(m_vertical);
		FlipLines(m_vertical, Height() - 1);
		
		reverse(m_horizontal);
		FlipLines(m_horizontal, Width() - 1);
	}
	else if (dir == Direction::West)
	{
		reverse(m_horizontal);
		FlipLines(m_vertical, Height() - 1);
		
		m_vertical.swap(m_horizontal);
	}
	
	SetOffset(offset);
	
	return *this;
}


int Area::MergeVectors_Begin(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	if (oa <= ob) return 0;
	
	auto diff = oa - ob;
	auto toCopy = min(oa - ob, (int)b.size());
	auto toFill = max(diff - (int)b.size(), 0);
	
	if (toCopy > 0)
	{
		a.insert(a.begin(), b.begin(), b.begin() + toCopy);
	}
	
	if (toFill > 0)
	{
		a.insert(a.begin() + toCopy, toFill, {});
	}
	
	return toCopy + toFill;
}

void Area::MergeVectors_Overlapping(int oa, int offset, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	int from	= max(oa, ob);
	int to		= min(oa + (int)a.size() - 1, ob + (int)b.size() - 1);
	
	// Offset is the part that was copied at the beginning, there is no need to merge it as it's going to be identical.
	from = from + offset;
	
	for (int i = from; i <= to; i++)
	{
		a[i - oa] |= b[i - ob];
	}
}

void Area::MergeVectors_End(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	auto last_a = oa + (int)a.size() - 1;
	auto last_b = ob + (int)b.size() - 1;
	
	auto toFill = ob - last_a - 1;
	auto toCopy = last_b - last_a;
	
	if (toFill >= 0)
	{
		if (toFill)
		{
			a.insert(a.end(), toFill, {});
		}
		
		a.insert(a.end(), b.begin(), b.end());
	}
	else if (toCopy > 0)
	{
		a.insert(a.end(), b.end() - toCopy, b.end());
	}
}


v2i Area::GetCommonRange(int oa, const vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	return v2i {max(oa, ob), min(oa + (int)a.size() - 1, ob + (int)b.size() - 1) };
}

int Area::CleanUp(vector<AreaLine> &a)
{
	int index = 0;
	int offset;
	
	for (const auto& l : a)
	{
		if (l.IsEmpty())
		{
			index++;
		}
		else
		{
			break;
		}
	}
	
	offset = index;
	
	if (index == a.size() - 1)
	{
		a.clear();
		return offset;
	}
	
	remove_until_index(a, index);
	
	for (auto i = (int)(a.size() - 1); i >= 0; i--)
	{
		if (!a[i].IsEmpty())
		{
			index = i;
			break;
		}
	}
	
	remove_after_index(a, index);
	
	return offset;
}

int Area::SubtractVectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	v2i common = GetCommonRange(oa, a, ob, b);
	
	if (common.x > common.y)
		return -1;
	
	for (auto i = common.x; i <= common.y; i++)
	{
		a[i - oa] -= b[i - ob];
	}
	
	return CleanUp(a);
}

int Area::IntersectVectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	v2i common = GetCommonRange(oa, a, ob, b);
	
	if (common.x > common.y)
		return -1;
	
	int removeBefore = common.x - oa;
	int removeAfter = -1;
	bool isEmptyMerge = true;
	
	for (auto i = common.x; i <= common.y; i++)
	{
		auto a_index	= i - oa;
		auto b_index	= i - ob;
		
		auto& line_a = a[a_index];
		auto& line_b = b[b_index];
		
		line_a &= line_b;
		
		if (!line_a.IsEmpty())
		{
			isEmptyMerge = false;
			removeAfter = a_index;
		}
		else if (isEmptyMerge)
		{
			removeBefore++;
		}
	}
	
	if (removeAfter < removeBefore)
	{
		return -1;
	}
	
	if (removeAfter < a.size() - 1)	remove_after_index(a, removeAfter);
	if (removeBefore > 0)			remove_until_index(a, removeBefore);
	
	return removeBefore;
}

int Area::MergeVectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	auto diff = MergeVectors_Begin(oa, a, ob, b);
	MergeVectors_Overlapping(oa - diff, diff, a, ob, b);
	MergeVectors_End(oa - diff, a, ob, b);
	
	return diff;
}

uint64_t Area::GetArea() const
{
	uint64_t sum = 0;
	
	for (auto& v : m_vertical)
	{
		sum += v.Area();
	}
	
	return sum;
}

Area& Area::operator|=(const Area &a)
{
	if (a.IsEmpty()) return *this;
	else if (IsEmpty()) { *this = a; return *this; }
	
	m_offset.x -= MergeVectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	m_offset.y -= MergeVectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}

Area& Area::operator&=(const Area &a)
{
	if (a.IsEmpty()) { *this = a; return *this; }
	else if (IsEmpty()) return *this;
	
	auto diff = IntersectVectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	
	if (diff == -1)
	{
		Clear();
		return *this;
	}
	
	m_offset.x += diff;
	m_offset.y += IntersectVectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}

Area& Area::operator-=(const Area &a)
{
	if (IsEmpty() || a.IsEmpty()) return *this;
	
	int offset = SubtractVectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	
	if (offset == -1)
	{
		return *this;
	}
	else if (m_vertical.empty())
	{
		Clear();
		return *this;
	}
	
	m_offset.x += offset;
	m_offset.y += SubtractVectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}


string Area::DebugInfo(char fill, char empty, bool withBoarder) const
{
	set<v2i> set;
	stringstream ss;
	
	for (const auto& n : *this)
	{
		set.insert(n);
	}
	
	if (withBoarder)
	{
		ss << "+" << string(Right() + 1, '-') << '+' << endl;
	}
	
	for (int y = Top(); y >= 0; y--)
	{
		if (withBoarder)
		{
			ss << "|";
		}
		
		for (int x = 0; x <= Right(); x++)
		{
			if (set.find(v2i(x, y)) != set.end())
			{
				ss << fill;
			}
			else
			{
				ss << empty;
			}
		}
		
		if (withBoarder)
		{
			ss << "|";
		}
		
		ss << endl;
	}
	
	if (withBoarder)
	{
		ss << "+" << string(Right() + 1, '-') << '+';
	}
	
	return ss.str();
}

bool Area::operator[](v2i at)
{
	at.x -= m_offset.x;
	
	if (at.x < 0 || at.x >= m_vertical.size())
	{
		return false;
	}
	
	return m_vertical[at.x].Contains(at);
}
