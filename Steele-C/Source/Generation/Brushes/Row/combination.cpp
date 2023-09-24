#include "combination.h"


#include <set>
#include <iostream>


using namespace Steele;
using namespace Steele::combination;


void combination::reduce(std::set<int>& source)
{
	std::vector<int> toRemove;
	
	for (auto a : source)
	{
		for (auto b : source)
		{
			if (a != b && a % b == 0)
			{
				toRemove.push_back(a);
			}
		}
	}
	
	for (auto i : toRemove)
	{
		source.erase(i);
	}
}

bool Steele::combination::can_be_combined(int total, const std::set<int>& parts)
{
	std::set<int> current = parts;
	std::set<int> next = {};
	
	for (auto i : current)
	{
		if (total % i == 0)
			return true;
		if (i < total)
			next.insert(i);
	}
	
	current.swap(next);
	
	while (!current.empty())
	{
		next.clear();
		
		for (auto c : current)
		{
			for (auto i : parts)
			{
				auto val = c + i;
				auto diff = total - val;
				
				if (val > total)
					continue;
				if (total % val == 0 || diff % i == 0 || diff % val == 0)
					return true;
				
				if (total > 1000)
				{
					for (auto n : next)
					{
						if (diff % n == 0)
						{
							return true;
						}
					}
				}
				
				if (total > val)
				{
					next.insert(val);
				}
			}
		}
		
		current.swap(next);
	}
	
	return false;
}


void Steele::to_combination_set(int total, std::set<int>& parts)
{
	std::vector<int> toRemove = {};
	
	for (auto it = parts.begin(); it != parts.end();)
	{
		auto val = *it;
		
		if (val <= 0 || val > total || !can_be_combined(total - val, parts)) 
		{
			it = parts.erase(it);
		}
		else
		{
			it++;
		}
	}
}