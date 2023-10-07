#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "../../test_utils.h"


#include "json.h"
#include "DataTypes/Map/Ground.h"


using namespace Steele;


TEST(GroundTile__JSON)
{
	nlohmann::json j;
	auto& map = IDMap::global();
	GroundTile original;
	GroundTile result;
	
	map.debug_add(1, "Hello World");
	map.debug_add(2, "Something else");
	map.debug_add(3, "Segfault");
	
	original.Dir = Direction::SouthWest;
	original.Index = 2;
	original.ID = 2;
	
	
	j = original;
	result = j;
	
	
	ASSERT_IS(original.Dir, result.Dir);
	ASSERT_IS(original.ID, result.ID);
}

TEST(Ground__JSON)
{
	nlohmann::json j;
	auto& map = IDMap::global();
	Ground original;
	Ground result;
	
	map.debug_add(1, "Hello World");
	map.debug_add(2, "Something else");
	map.debug_add(3, "Segfault");
	
	original.add(2, Direction::East, 4);
	original.add(1, Direction::SouthWest, 1);
	original.add(3, Direction::NorthWest, 3);
	
	
	j = original;
	result = j;
	
	
	ASSERT_IS(result.size(), 3);
	
	auto& first = *(result.begin());
	auto& second = *(result.begin() + 1);
	auto& third = *(result.begin() + 2);
	
	ASSERT_IS(first.Dir,	Direction::SouthWest);
	ASSERT_IS(second.Dir,	Direction::NorthWest);
	ASSERT_IS(third.Dir,	Direction::East);
	
	ASSERT_IS(first.Index,	0);
	ASSERT_IS(second.Index,	1);
	ASSERT_IS(third.Index,	2);
	
	ASSERT_IS(first.ID,		1);
	ASSERT_IS(second.ID,	3);
	ASSERT_IS(third.ID,		2);
}


#pragma clang diagnostic pop
