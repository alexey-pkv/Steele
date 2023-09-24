#ifndef STEELE_COMBINATION_H
#define STEELE_COMBINATION_H


#include <set>
#include <vector>


namespace Steele
{
	void to_combination_set(int total, std::set<int>& parts);
	
	
	namespace combination
	{
		bool can_be_combined(int total, const std::set<int>& parts);
		void reduce(std::set<int>& source);
	}
}


#endif
