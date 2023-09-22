#include <set>
#include <string>
#include <sstream>
#include <algorithm>


#include "Area.h"
#include "Types.h"
#include "Utils.h"


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

Area::Area(v2i v):
	Area(r2i(v, v2i_one))
{
	
}

Area::Area(int x, int y, int to_x, int to_y) : 
	Area(r2i(x, y, to_x - x + 1, to_y - y + 1))
{
	
}

Area::Area(int at_x, int at_y) : 
	Area(r2i(at_x, at_y, 1, 1))
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


void Area::clear()
{
	m_vertical.clear();
	m_horizontal.clear();
	m_offset = v2i_zero;
}

void Area::clean_up()
{
	m_offset.x += clean_up(m_vertical);
	
	if (m_vertical.empty())
	{
		m_horizontal.clear();
		m_offset = v2i_zero;
	}
	else
	{
		m_offset.y += clean_up(m_horizontal);
	}
}

void Area::offset_all(vector<AreaLine> &lines, int by)
{
	if (by == 0) return;
	
	for (auto& line : lines)
	{
		line >>= by;
	}
}

void Area::flip_lines(vector<AreaLine>& lines, int offset)
{
	for (auto& n : lines)
	{
		n.flip(offset);
	}
}

Area& Area::operator*=(Direction dir)
{
	if (dir == Direction::North) return *this;
	
	auto offset = m_offset;
	
	reset_offset();
	
	if (dir == Direction::East)
	{
		reverse(m_vertical);
		flip_lines(m_horizontal, width() - 1);
		
		m_vertical.swap(m_horizontal);
	}
	else if (dir == Direction::South)
	{
		reverse(m_vertical);
		flip_lines(m_vertical, height() - 1);
		
		reverse(m_horizontal);
		flip_lines(m_horizontal, width() - 1);
	}
	else if (dir == Direction::West)
	{
		reverse(m_horizontal);
		flip_lines(m_vertical, height() - 1);
		
		m_vertical.swap(m_horizontal);
	}
	
	set_offset(offset);
	
	return *this;
}


int Area::merge_vectors_begin(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
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

void Area::merge_vectors_overlapping(int oa, int offset, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	int from	= max(oa, ob);
	int to		= min(oa + (int)a.size() - 1, ob + (int)b.size() - 1);
	
	// offset is the part that was copied at the beginning, there is no need to merge it as it's going to be identical.
	from = from + offset;
	
	for (int i = from; i <= to; i++)
	{
		a[i - oa] |= b[i - ob];
	}
}

void Area::merge_vectors_end(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
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


v2i Area::get_common_range(int oa, const vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	return v2i {max(oa, ob), min(oa + (int)a.size() - 1, ob + (int)b.size() - 1) };
}

int Area::clean_up(vector<AreaLine> &a)
{
	int index = 0;
	int offset;
	
	for (const auto& l : a)
	{
		if (l.is_empty())
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
		if (!a[i].is_empty())
		{
			index = i;
			break;
		}
	}
	
	remove_after_index(a, index);
	
	return offset;
}

int Area::subtract_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	v2i common = get_common_range(oa, a, ob, b);
	
	if (common.x > common.y)
		return -1;
	
	for (auto i = common.x; i <= common.y; i++)
	{
		a[i - oa] -= b[i - ob];
	}
	
	return clean_up(a);
}

int Area::intersect_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	v2i common = get_common_range(oa, a, ob, b);
	
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
		
		if (!line_a.is_empty())
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

int Area::merge_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b)
{
	auto diff = merge_vectors_begin(oa, a, ob, b);
	merge_vectors_overlapping(oa - diff, diff, a, ob, b);
	merge_vectors_end(oa - diff, a, ob, b);
	
	return diff;
}

uint64_t Area::get_area() const
{
	uint64_t sum = 0;
	
	for (auto& v : m_vertical)
	{
		sum += v.area();
	}
	
	return sum;
}

Area& Area::operator|=(const Area &a)
{
	if (a.is_empty()) return *this;
	else if (is_empty()) { *this = a; return *this; }
	
	m_offset.x -= merge_vectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	m_offset.y -= merge_vectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}

Area& Area::operator&=(const Area &a)
{
	if (a.is_empty()) { *this = a; return *this; }
	else if (is_empty()) return *this;
	
	auto diff = intersect_vectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	
	if (diff == -1)
	{
		clear();
		return *this;
	}
	
	m_offset.x += diff;
	m_offset.y += intersect_vectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}

Area& Area::operator-=(const Area &a)
{
	if (is_empty() || a.is_empty()) return *this;
	
	int offset = subtract_vectors(m_offset.x, m_vertical, a.m_offset.x, a.m_vertical);
	
	if (offset == -1)
	{
		return *this;
	}
	else if (m_vertical.empty())
	{
		clear();
		return *this;
	}
	
	m_offset.x += offset;
	m_offset.y += subtract_vectors(m_offset.y, m_horizontal, a.m_offset.y, a.m_horizontal);
	
	return *this;
}


string Area::debug_info(char fill, char empty, bool withBoarder) const
{
	set<v2i> set;
	stringstream ss;
	
	for (const auto& n : *this)
	{
		set.insert(n);
	}
	
	if (withBoarder)
	{
		ss << "+" << string(right() + 1, '-') << '+' << endl;
	}
	
	for (int y = top(); y >= 0; y--)
	{
		if (withBoarder)
		{
			ss << "|";
		}
		
		for (int x = 0; x <= right(); x++)
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
		ss << "+" << string(right() + 1, '-') << '+';
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
	
	return m_vertical[at.x].contains(at);
}

bool Area::overlaps(const Area &a) const
{
	auto myOffset = m_offset.x;
	auto aOffset = a.m_offset.x; 
	
	v2i common = get_common_range(myOffset, m_vertical, aOffset, a.m_vertical);
	
	if (common.x > common.y)
		return false;
	
	for (auto i = common.x; i <= common.y; i++)
	{
		auto my_index= i - myOffset;
		auto a_index	= i - aOffset;
		
		auto& my_line = m_vertical[my_index];
		auto& a_line = a.m_vertical[a_index];
		
		if (my_line && a_line)
		{
			return true;
		}
	}
	
	return false;
}

bool Area::operator>=(const Area &a) const
{
	if (a.is_empty()) return true;
	else if (is_empty()) return false;
	
	if (a.left() < left() || a.right() > right() ||
		a.bottom() < bottom() || a.top() > top())
	{
		return false;
	}
	
	auto size = a.m_vertical.size();
	auto offset = a.left() - left();
	
	for (int i = 0; i < size; i++)
	{
		if (!m_vertical[i + offset].contains(a.m_vertical[i]))
		{
			return false;
		}
	}
	
	return true;
}

bool Area::contains(const v2i& v) const
{
	int x = v.x - m_offset.x;
	
	if (x < 0 || x >= m_vertical.size())
	{
		return false;
	}
	
	return m_vertical[x].contains(v.y);
}


void Area::set_offset(v2i v)
{
	if (is_empty() || m_offset == v) 
		return;
	
	auto diff = v - m_offset;
	
	m_offset = v;
	
	if (diff.x != 0)
	{
		offset_all(m_horizontal, diff.x);
	}
	
	if (diff.y != 0)
	{
		offset_all(m_vertical, diff.y);
	}
}


const Area Area::ZERO	= {};
const Area Area::ONE	= Area("*\n");