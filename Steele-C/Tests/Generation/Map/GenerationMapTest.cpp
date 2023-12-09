#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "../../test_utils.h"


#include "Generation/Map/GenerationMap.h"


using namespace Steele;


TEST(Generation__Common_Case)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	
	ASSERT_IS(nullptr, gm.try_get(1, 1));
	ASSERT_IS_NOT(nullptr, gm.get(1, 1));
	ASSERT_IS_NOT(nullptr, gm.try_get(1, 1));
}

TEST(Generation__Get__SameObject)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	
	ASSERT_IS(gm.get(1, 1), gm.get(1, 1));
	ASSERT_IS(gm.try_get(1, 1), gm.get(1, 1));
}

TEST(Generation__Get__DifferentObjects)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	
	ASSERT_IS_NOT(gm.get(1, 1), gm.get(1, 2));
	ASSERT_IS_NOT(gm.try_get(1, 1), gm.get(1, 2));
}


TEST(Generation__Remove__EmptyCell__NoChange)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	
	auto a = gm.get(1, 1);
	
	
	gm.get(1, 2);
	
	
	ASSERT_TRUE(gm.remove(1, 2));
	ASSERT_IS(a, gm.get(1, 1));
	ASSERT_IS(nullptr, gm.try_get(1, 2));
}


TEST(Generation__const_try_get__CellEmpty__ReturnNullPtr)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	const GenerationMap& cgm = gm;
	
	const auto c = cgm.try_get(1, 1);
	
	ASSERT_IS(nullptr, c);
}

TEST(Generation__const_try_get__CellSet__CellReturned)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	const GenerationMap& cgm = gm;
	
	gm.get(1, 1);
	
	const auto c = cgm.try_get(1, 1);
	
	ASSERT_IS_NOT(nullptr, c);
}


TEST(Generation__is_empty__NoCell__ReturnTrue)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	ASSERT_TRUE(gm.is_empty(1, 1));
}

TEST(Generation__is_empty__CellExists__ReturnFalse)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	gm.get(1, 1);
	
	
	ASSERT_FALSE(gm.is_empty(1, 1));
}

TEST(Generation__remove__NoStacks__CellRemoved)
{
	GenerationMap gm(make_shared<SimpleMap<Cell>>());
	
	gm.get(1, 1);
	
	
	ASSERT_TRUE(gm.remove(1, 1));
	ASSERT_NULL(gm.try_get(1, 1));
}


#pragma clang diagnostic pop