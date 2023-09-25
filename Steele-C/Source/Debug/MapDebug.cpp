#include "MapDebug.h"
#include "RNG/XoroshiroRNG.h"


using namespace std;
using namespace Steele;


string Steele::debug_info(const SimpleMap<Cell>& source)
{
	v2i min;
	v2i max;
	
	Steele::XoroshiroRNG rng(__FUNCTION__);
	const char* CHARS		= "1234567890-=!@#$%^&*()_+abcdefghijklmnopqrstvuwxyzABCDEFGHIJKLMNOPQRSTVUWXYZ,./;'[]<>?:\"{}`~";
	const size_t CHAR_COUNT	= strlen(CHARS);
	std::map<t_id, char>	ground_char_map = {};
	
	if (!source.size())
		return "";
	
	auto any = source.begin()->first;
	
	min = v2i(any.x, any.y);
	max = min;
	
	for (auto& n : source)
	{
		auto pos = n.first;
		
		min.x = std::min(pos.x, min.x);
		min.y = std::min(pos.y, min.y);
		max.x = std::max(pos.x, max.x);
		max.y = std::max(pos.y, max.y);
	}

	std::string res;
	
	for (auto y = min.y; y <= max.y; y++)
	{
		for (auto x = min.x; x <= max.x; x++)
		{
			auto* cell = source.try_get(x, y);
			char c = ' ';
			
			if (cell != nullptr && !cell->Ground.is_empty())
			{
				auto g_id = (*cell->Ground.begin()).ID;
				auto existing_char = ground_char_map.find(g_id);
				
				if (existing_char == ground_char_map.end())
				{
					auto index = rng.next_uint_64(0, CHAR_COUNT - 1);
					c = CHARS[index];
					
					ground_char_map[g_id] = c;
				}
				else
				{
					c = existing_char->second;
				}
			}
			
			res += c;
		}
		
		res += "\n";
	}
	
	return res;
}
