#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "../../test_utils.h"


#include "Generation/Map/GenerationMap.h"


using namespace Steele;


TEST(Generation__Common_Case)
{
	GenerationMap gm;
	
	ASSERT_IS(nullptr, gm.try_get(1, 1));
	ASSERT_IS_NOT(nullptr, gm.get(1, 1));
	ASSERT_IS_NOT(nullptr, gm.try_get(1, 1));
}

TEST(Generation__Get__SameObject)
{
	GenerationMap gm;
	
	ASSERT_IS(gm.get(1, 1), gm.get(1, 1));
	ASSERT_IS(gm.try_get(1, 1), gm.get(1, 1));
}

TEST(Generation__Get__DifferentObjects)
{
	GenerationMap gm;
	
	ASSERT_IS_NOT(gm.get(1, 1), gm.get(1, 2));
	ASSERT_IS_NOT(gm.try_get(1, 1), gm.get(1, 2));
}


TEST(Generation__Remove__EmptyCell__NoChange)
{
	GenerationMap gm;
	
	auto a = gm.get(1, 1);
	
	gm.get(1, 2);
	ASSERT_TRUE(gm.remove(1, 2));
	gm.try_get(1, 2);
	
	ASSERT_IS(a, gm.get(1, 1));
	ASSERT_IS(nullptr, gm.try_get(1, 2));
}


TEST(Generation__const_try_get__CellEmpty__ReturnNullPtr)
{
	GenerationMap gm;
	const GenerationMap& cgm = gm;
	
	const auto c = cgm.try_get(1, 1);
	
	ASSERT_IS(nullptr, c);
}

TEST(Generation__const_try_get__CellSet__CellReturned)
{
	GenerationMap gm;
	const GenerationMap& cgm = gm;
	
	gm.get(1, 1);
	
	const auto c = cgm.try_get(1, 1);
	
	ASSERT_IS_NOT(nullptr, c);
}


TEST(Generation__const_try_get__CellEmptyAndStuckExists__ReturnNullPtr)
{
	GenerationMap gm;
	const GenerationMap& cgm = gm;
	
	gm.checkpoint();
	
	const auto c = cgm.try_get(1, 1);
	
	ASSERT_IS(nullptr, c);
}

TEST(Generation__const_try_get__CellNotEmptyAndStuckExists__ReturnSameCell)
{
	GenerationMap gm;
	const GenerationMap& cgm = gm;
	
	auto original_cell = gm.get(1, 1);
	
	gm.checkpoint();
	
	auto c = cgm.try_get(1, 1);
	
	ASSERT_IS(original_cell, c);
}

TEST(Generation__const_try_get__MultipleStacksExists__AlwaysReturnSameCell)
{
	GenerationMap gm;
	const GenerationMap& cgm = gm;
	
	auto original_cell = gm.get(1, 1);
	
	gm.checkpoint();
	
	auto a = cgm.try_get(1, 1);
	
	gm.checkpoint();
	
	auto b = cgm.try_get(1, 1);
	
	ASSERT_IS(original_cell, a);
	ASSERT_IS(original_cell, b);
}


TEST(Generation__try_get__StackExists__ReturnNewCell)
{
	GenerationMap gm;
	
	auto original_cell = gm.get(1, 1);
	
	gm.checkpoint();
	
	auto c = gm.try_get(1, 1);
	
	ASSERT_IS_NOT(original_cell, c);
}

TEST(Generation__try_get__MultipleStacksExists__ReturnNewCell)
{
	GenerationMap gm;
	
	auto original_cell = gm.get(1, 1);
	
	gm.checkpoint();
	
	auto a = gm.try_get(1, 1);
	
	a->IsRoad = true;
	
	gm.checkpoint();
	
	auto b = gm.try_get(1, 1);
	
	ASSERT_IS_NOT(original_cell, a);
	ASSERT_IS_NOT(original_cell, b);
	ASSERT_IS_NOT(a, b);
}

TEST(Generation__checkpoint__MultipleStacksExists__ValueCopiedCorrectly)
{
	GenerationMap gm;
	
	auto original_cell = gm.get(1, 1);
	
	original_cell->Ground.add(1, Direction::North, 0);
	
	gm.checkpoint();
	
	auto a = gm.try_get(1, 1);
	
	a->Ground.add(2, Direction::North, 0);
	
	gm.checkpoint();
	
	auto b = gm.try_get(1, 1);
	
	b->Ground.add(3, Direction::North, 0);
	
	
	ASSERT_IS(original_cell->Ground[0].ID, 1);
	ASSERT_IS(original_cell->Ground.size(), 1);
	
	ASSERT_IS(a->Ground[0].ID, 1);
	ASSERT_IS(a->Ground[1].ID, 2);
	ASSERT_IS(a->Ground.size(), 2);
	
	ASSERT_IS(b->Ground[0].ID, 1);
	ASSERT_IS(b->Ground[1].ID, 2);
	ASSERT_IS(b->Ground[2].ID, 3);
	ASSERT_IS(b->Ground.size(), 3);
}

TEST(Generation__rollback__MultipleStacksExists__ReturnPreviousValue)
{
	GenerationMap gm;
	
	auto original_cell = gm.get(1, 1);
	
	original_cell->Ground.add(1, Direction::North, 0);
	
	gm.checkpoint();
	
	auto a = gm.try_get(1, 1);
	
	a->Ground.add(2, Direction::North, 0);
	
	gm.checkpoint();
	
	auto b = gm.try_get(1, 1);
	
	b->Ground.add(3, Direction::North, 0);
	
	gm.rollback();
	
	auto final = gm.try_get(1, 1);
	
	ASSERT_IS(final, a);
	ASSERT_IS(final->Ground[0].ID, 1);
	ASSERT_IS(final->Ground[1].ID, 2);
}


#pragma clang diagnostic pop