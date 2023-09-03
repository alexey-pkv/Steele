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
	
	
	ASSERT_IS(original_cell->Ground[0]->ID, 1);
	ASSERT_IS(original_cell->Ground.size(), 1);
	
	ASSERT_IS(a->Ground[0]->ID, 1);
	ASSERT_IS(a->Ground[1]->ID, 2);
	ASSERT_IS(a->Ground.size(), 2);
	
	ASSERT_IS(b->Ground[0]->ID, 1);
	ASSERT_IS(b->Ground[1]->ID, 2);
	ASSERT_IS(b->Ground[2]->ID, 3);
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
	ASSERT_IS(final->Ground[0]->ID, 1);
	ASSERT_IS(final->Ground[1]->ID, 2);
}

TEST(Generation__rollback__CellNotSet__NewValueIsRolledBack)
{
	GenerationMap gm;
	
	gm.checkpoint();
	
	auto a = gm.try_get(1, 1);
	ASSERT_IS(nullptr, a);
	
	gm.checkpoint();
	
	auto b = gm.get(1, 1);
	b->Ground.add(1, Direction::North, 0);
	
	gm.rollback();
	
	auto final = gm.try_get(1, 1);
	
	ASSERT_IS(nullptr, final);
}

TEST(Generation__commit__PreviousCellIsModified)
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
	
	
	gm.commit();
	
	
	auto final = gm.try_get(1, 1);
	
	ASSERT_IS(final, a);
	ASSERT_IS_NOT(final, b);
	ASSERT_IS(final->Ground.size(), 3);
	ASSERT_IS(final->Ground[0]->ID, 1);
	ASSERT_IS(final->Ground[1]->ID, 2);
	ASSERT_IS(final->Ground[2]->ID, 3);
}

TEST(Generation__commit__CellDoesNotExists__PreviousCellIsModified)
{
	GenerationMap gm;
	
	gm.checkpoint();
	auto a = gm.try_get(1, 1);
	gm.checkpoint();
	auto b = gm.get(1, 1);
	b->Ground.add(1, Direction::North, 0);
	
	
	gm.commit();
	
	
	auto final = gm.try_get(1, 1);
	
	ASSERT_IS_NOT(final, b);
	ASSERT_IS(final->Ground.size(), 1);
	ASSERT_IS(final->Ground[0]->ID, 1);
}

TEST(Generation__commit__CellIsDeleted__ExistingCellRemvoed)
{
	GenerationMap gm;
	
	gm.checkpoint();
	gm.get(1, 1);
	gm.checkpoint();
	gm.remove(1, 1);
	
	
	gm.commit();
	
	
	ASSERT_NULL(gm.try_get(1, 1));
}


TEST(Generation__set__CellWasRemoved__CellValueSetCorrecty)
{
	GenerationMap gm;
	
	gm.checkpoint();
	gm.get(1, 1);
	gm.get(2, 2);
	gm.checkpoint();
	gm.remove(1, 1);
	
	gm.set({}, 1, 1);
	gm.remove(2, 2);
	
	ASSERT_NOT_NULL(gm.try_get(1, 1));
	ASSERT_NULL(gm.try_get(2, 2));
}

TEST(Generation__set__CellValueUpdated)
{
	GenerationMap gm;
	Cell c(2, Direction::West, 2);
	
	gm.checkpoint();
	auto b = gm.get(1, 1);
	b->Ground.add(1, Direction::North, 1);
	
	gm.set(c, 1, 1);
	
	
	auto result = gm.get(1, 1);
	
	
	ASSERT_IS(result, b);
	ASSERT_IS(result->Ground.size(), 1);
	ASSERT_IS(result->Ground[0]->ID, 2);
}


TEST(Generation__is_empty__NoCell__ReturnTrue)
{
	GenerationMap gm;
	ASSERT_TRUE(gm.is_empty(1, 1));
}

TEST(Generation__is_empty__CellExists__ReturnFalse)
{
	GenerationMap gm;
	gm.get(1, 1);
	
	
	ASSERT_FALSE(gm.is_empty(1, 1));
}

TEST(Generation__is_empty__CellSetInStack__ReturnTrue)
{
	GenerationMap gm;
	
	gm.checkpoint();
	gm.get(1, 1);
	
	
	ASSERT_FALSE(gm.is_empty(1, 1));
}

TEST(Generation__is_empty__CellRemovedInStack__ReturnFalse)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	gm.checkpoint();
	gm.remove(1, 1);
	
	
	ASSERT_TRUE(gm.is_empty(1, 1));
}

TEST(Generation__remove__NoStacks__CellRemoved)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	
	
	ASSERT_TRUE(gm.remove(1, 1));
	ASSERT_NULL(gm.try_get(1, 1));
}

TEST(Generation__remove__CellRemoved__ReturnNull)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	gm.checkpoint();
	
	
	gm.remove(1, 1);
	
	auto b = gm.try_get(1, 1);
	
	ASSERT_NULL(gm.try_get(1, 1));
}

TEST(Generation__remove__CellRemoved__ReturnNullInNextStack)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	gm.checkpoint();
	gm.remove(1, 1);
	gm.checkpoint();
	
	
	ASSERT_NULL(gm.try_get(1, 1));
}

TEST(Generation__remove__CellRemovedResetRemvoed__ReturnNull)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	gm.checkpoint();
	gm.remove(1, 1);
	gm.checkpoint();
	gm.get(1, 1);
	gm.checkpoint();
	gm.remove(1, 1);
	
	
	ASSERT_NULL(gm.try_get(1, 1));
	gm.checkpoint();
	ASSERT_NULL(gm.try_get(1, 1));
}


TEST(Generation__rollback__ResetCorrectlyRemovedCells)
{
	GenerationMap gm;
	
	auto b = gm.get(1, 1);
	
	gm.checkpoint();
	{
		gm.remove(1, 1);
		gm.checkpoint();
		{
			auto a = gm.get(1, 1);
			gm.checkpoint();
			{
				gm.remove(1, 1);
				gm.checkpoint();
				{
					ASSERT_NULL(gm.try_get(1, 1));
				}
				gm.rollback();
				ASSERT_NULL(gm.try_get(1, 1));
			}
			gm.rollback();
			ASSERT_IS(a, gm.try_get(1, 1));
		}
		gm.rollback();
		ASSERT_NULL(gm.try_get(1, 1));
	}
	gm.rollback();
	
	ASSERT_IS(b, gm.try_get(1, 1));
}

TEST(Generation__rollback__ResetCorrectlyPreviousCells)
{
	GenerationMap gm;
	
	auto b = gm.get(1, 1);
	b->Ground.add(0, Direction::North, 0);
	
	gm.checkpoint();
	{
		auto c = gm.get(1, 1);
		c->Ground.add(1, Direction::North, 1);
	
		gm.checkpoint();
		{
			auto d = gm.get(1, 1);
			d->Ground.add(2, Direction::North, 1);
			
			gm.checkpoint();
			{
				auto e = gm.get(1, 1);
				e->Ground.add(3, Direction::North, 1);
			}
			gm.rollback();
			
			ASSERT_IS(d, gm.try_get(1, 1));
			ASSERT_IS(d->Ground.size(), 3);
			ASSERT_IS(d->Ground[0]->ID, 0);
			ASSERT_IS(d->Ground[1]->ID, 1);
			ASSERT_IS(d->Ground[2]->ID, 2);
		}
		gm.rollback();
		
		ASSERT_IS(c, gm.try_get(1, 1));
		ASSERT_IS(c->Ground.size(), 2);
		ASSERT_IS(c->Ground[0]->ID, 0);
		ASSERT_IS(c->Ground[1]->ID, 1);
	}
	gm.rollback();
	
	ASSERT_IS(b, gm.try_get(1, 1));
	ASSERT_IS(b->Ground.size(), 1);
}

TEST(Generation__commit__CommitCorrectlyRemovedCells)
{
	GenerationMap gm;
	
	gm.get(1, 1);
	
	gm.checkpoint();
	{
		gm.remove(1, 1);
		gm.checkpoint();
		{
			auto a = gm.get(1, 1);
			gm.checkpoint();
			{
				gm.remove(1, 1);
				gm.checkpoint();
				{
					ASSERT_NULL(gm.try_get(1, 1));
				}
				gm.commit();
				ASSERT_NULL(gm.try_get(1, 1));
			}
			gm.commit();
			ASSERT_NULL(gm.try_get(1, 1));
		}
		gm.commit();
		ASSERT_NULL(gm.try_get(1, 1));
	}
	gm.commit();
	
	ASSERT_NULL(gm.try_get(1, 1));
}

TEST(Generation__commit__CorrectlyCommitValue)
{
	GenerationMap gm;
	
	auto b = gm.get(1, 1);
	b->Ground.add(0, Direction::North, 0);
	
	gm.checkpoint();
	{
		auto c = gm.get(1, 1);
		c->Ground.add(1, Direction::North, 1);
	
		gm.checkpoint();
		{
			auto d = gm.get(1, 1);
			d->Ground.add(2, Direction::North, 1);
			
			gm.checkpoint();
			{
				auto e = gm.get(1, 1);
				e->Ground.add(3, Direction::North, 1);
			}
			gm.commit();
			
			ASSERT_IS(d, gm.try_get(1, 1));
			ASSERT_IS(d->Ground.size(), 4);
			ASSERT_IS(d->Ground[0]->ID, 0);
			ASSERT_IS(d->Ground[1]->ID, 1);
			ASSERT_IS(d->Ground[2]->ID, 2);
			ASSERT_IS(d->Ground[3]->ID, 3);
		}
		gm.commit();
		
		ASSERT_IS(c, gm.try_get(1, 1));
		ASSERT_IS(c->Ground.size(), 4);
		ASSERT_IS(c->Ground[0]->ID, 0);
		ASSERT_IS(c->Ground[1]->ID, 1);
		ASSERT_IS(c->Ground[2]->ID, 2);
		ASSERT_IS(c->Ground[3]->ID, 3);
	}
	
	gm.commit();
	
	ASSERT_IS(b, gm.try_get(1, 1));
	ASSERT_IS(b->Ground.size(), 4);
	ASSERT_IS(b->Ground[0]->ID, 0);
	ASSERT_IS(b->Ground[1]->ID, 1);
	ASSERT_IS(b->Ground[2]->ID, 2);
	ASSERT_IS(b->Ground[3]->ID, 3);
}

TEST(Generation__commit__CommitAfterRollback__LatestValueStored)
{
	GenerationMap gm;
	
	auto b = gm.get(1, 1);
	b->Ground.add(0, Direction::North, 0);
	
	gm.checkpoint();
	{
		auto c = gm.get(1, 1);
		c->Ground.add(1, Direction::North, 1);
	
		gm.checkpoint();
		{
			auto d = gm.get(1, 1);
			d->Ground.add(2, Direction::North, 1);
			
			gm.checkpoint();
			{
				auto e = gm.get(1, 1);
				e->Ground.add(3, Direction::North, 1);
			}
			gm.commit();
		}
		
		
		gm.rollback();
	}
	gm.commit();
	
	
	ASSERT_IS(b, gm.try_get(1, 1));
	ASSERT_IS(b->Ground.size(), 2);
	ASSERT_IS(b->Ground[0]->ID, 0);
	ASSERT_IS(b->Ground[1]->ID, 1);
}


TEST(Generation__commit__RollBackAfterCommit__ValueRestored)
{
	GenerationMap gm;
	
	auto b = gm.get(1, 1);
	b->Ground.add(0, Direction::North, 0);
	
	gm.checkpoint();
	{
		auto c = gm.get(1, 1);
		c->Ground.add(1, Direction::North, 1);
	
		gm.checkpoint();
		{
			auto d = gm.get(1, 1);
			d->Ground.add(2, Direction::North, 1);
			
			gm.checkpoint();
			{
				auto e = gm.get(1, 1);
				e->Ground.add(3, Direction::North, 1);
			}
			gm.commit();
		}
		
		
		gm.commit();
	}
	gm.rollback();
	
	
	ASSERT_IS(b, gm.try_get(1, 1));
	ASSERT_IS(b->Ground.size(), 1);
	ASSERT_IS(b->Ground[0]->ID, 0);
}


TEST(Generation__stack_depth)
{
	GenerationMap gm;
	
	ASSERT_IS(0, gm.stack_depth());
	gm.checkpoint();
	ASSERT_IS(1, gm.stack_depth());
	gm.checkpoint();
	ASSERT_IS(2, gm.stack_depth());
	gm.rollback();
	ASSERT_IS(1, gm.stack_depth());
	gm.commit();
	ASSERT_IS(0, gm.stack_depth());
}


TEST(Generation__is_in_checkpoint)
{
	GenerationMap gm;
	
	ASSERT_FALSE(gm.is_in_checkpoint());
	gm.checkpoint();
	ASSERT_TRUE(gm.is_in_checkpoint());
	gm.checkpoint();
	ASSERT_TRUE(gm.is_in_checkpoint());
	gm.rollback();
	ASSERT_TRUE(gm.is_in_checkpoint());
	gm.commit();
	ASSERT_FALSE(gm.is_in_checkpoint());
}


#pragma clang diagnostic pop