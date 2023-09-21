#include "VoronoiSquareGenerator.h"
#include "RNG/XoroshiroRNG.h"


bool Steele::VoronoiSquareGenerator::place_centers(int centers)
{
	for (int i = 0; i < centers; i++)
	{
		bool placed = false;
		
		for (int a = 0; !placed && a < 1000; a++)
		{
			auto x = m_rng->next_int_32(0, m_size.x - 1);
			auto y = m_rng->next_int_32(0, m_size.y - 1);
			
			if (!m_map.is_empty({x, y}))
				continue;
		
			placed = true;
			m_centers.emplace_back();
			
			auto& region = m_centers.back();
			
			region.Sign = '\0';
			region.TotalArea = Area(v2i { x, y });
			region.Center = { x, y };
			
			m_toFill.insert(i);
		}
		
		if (!placed)
		{
			return false;
		}
	}
	
	m_centers.reserve(centers);
	
	for (auto& v : m_centers)
	{
		m_map.set(&v, v.Center);
	}
	
	return true;
}


bool Steele::VoronoiSquareGenerator::fill_direction(Steele::VoronoiSquareGenerator::CenterInfo& center, v2i dir)
{
	bool found = false;
	
	auto pos = center.Center;
	auto dis = center.Distance;
	auto offset = dir * (dis + 1);
	auto neighbor_offset = dir * dis;
	auto change = abs(dir);
	auto iterator = v2i { change.y, change.x };
	
	for (auto currIndex = -dis; currIndex <= dis; currIndex++)
	{
		auto curr = v2i { offset + iterator * currIndex } + pos;
		auto neighbor = v2i { neighbor_offset + iterator * currIndex } + pos;
		
		if (curr.x < 0 || curr.y < 0 || curr.x >= m_size.x || curr.y >= m_size.y)
			continue;
		
		if (!m_map.is_empty(curr))
			continue;
		
		auto val = m_map.try_get(neighbor);
		
		if (!val || !(*val) || (*val) != &center)
			continue;
		
		m_map.set(&center, curr);
		center.TotalArea |= Area(curr);
		
		found = true;
	}
	
	return found;
}

bool Steele::VoronoiSquareGenerator::fill_once(Steele::VoronoiSquareGenerator::CenterInfo& center)
{
	bool changed = false;
	
	if (fill_direction(center, { -1, 0 }))	changed = true;
	if (fill_direction(center, { 1, 0 }))	changed = true;
	if (fill_direction(center, { 0, -1 }))	changed = true;
	if (fill_direction(center, { 0, 1 }))	changed = true;
	
	return changed;
}

bool Steele::VoronoiSquareGenerator::fill_once_corner(Steele::VoronoiSquareGenerator::CenterInfo& center, v2i corner)
{
	auto offset_x = v2i { corner.x, 0 };
	auto offset_y = v2i { 0, 		corner.y };
	
	auto dis = center.Distance;
	auto pos = center.Center;
	auto curr = pos + corner * (dis + 1);
	
	if (curr.x < 0 || curr.y < 0 || curr.x >= m_size.x || curr.y >= m_size.y)
		return false;
	
	if (!m_map.is_empty(curr))
		return false;
	
	auto neighbor_x = pos + corner * dis + offset_x;
	auto neighbor_y = pos + corner * dis + offset_y;
	
	auto val_x = m_map.try_get(neighbor_x);
	auto val_y = m_map.try_get(neighbor_y);
	
	if (!val_x || !(*val_x) || (*val_x) != &center) return false;
	if (!val_y || !(*val_y) || (*val_y) != &center) return false;
	
	m_map.set(&center, curr);
	center.TotalArea |= Area(curr);
	
	return true;
}

bool Steele::VoronoiSquareGenerator::fill_once_corners(Steele::VoronoiSquareGenerator::CenterInfo& center)
{
	bool changed = false;
	
	if (fill_once_corner(center, { -1, -1 }))	changed = true;
	if (fill_once_corner(center, { -1, 1 }))	changed = true;
	if (fill_once_corner(center, { 1, -1 }))	changed = true;
	if (fill_once_corner(center, { 1, 1 }))	changed = true;
	
	return changed;
}



bool Steele::VoronoiSquareGenerator::fill_once()
{
	auto toFill = m_toFill;
	bool found = false;
	
	for (auto index : toFill)
	{
		auto& center = m_centers[index];
		
		if (!fill_once(center))
		{
			m_toFill.erase(index);
			center.Complete = true;
		}
		else
		{
			fill_once_corners(center);
			center.Distance++;
			found = true;
		}
	}
	
	return found;
}


bool Steele::VoronoiSquareGenerator::generate(Steele::IRNG& rng, v2i size, int centers)
{
	m_rng = &rng;
	m_size = size;
	
	if (!place_centers(centers))
		return false;
	
	while (!m_toFill.empty())
	{
		if (!fill_once())
		{
			return false;
		}
	}
	
	return true;
}

bool Steele::VoronoiSquareGenerator::generate_avg(Steele::IRNG& rng, v2i size, int avg_area)
{
	auto area = size.x * size.y;
	int centers = (int)round((double)area / (double)avg_area);
	
	if (centers == 0)
		return false;
	
	return generate(rng, size, centers);
}


std::string Steele::VoronoiSquareGenerator::debug_info() const
{
	const char*			 	chrs = "`~!@#$%^&*()_+<>?,./:\";'[]{}\\|01234567890abcdefghijklmnopqrstvuwxyz";
	int 					chr_i = 0;
	auto					char_size = strlen(chrs);
	Steele::XoroshiroRNG	rng(chrs);
	
	std::string result;
	
	for (int x = 0; x < m_size.x; x++)
	{
		for (int y = 0; y < m_size.y; y++)
		{
			auto val = m_map.try_get(x, y);
			
			if (!val || !(*val))
			{
				result += " ";
				continue;
			}
			
			char c;
			auto info_p = *val;
			
			if (info_p->Sign == '\0')
			{
				c = chrs[rng.next<size_t>(0, char_size - 1)];
				info_p->Sign = c;
			}
			else
			{
				c = info_p->Sign;
			}
			
			result += c;
		}
		
		result += "\n";
	}
	
	return result;
}
