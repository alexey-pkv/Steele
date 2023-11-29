#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "../../../test_utils.h"

#include "DataTypes/Area.h"
#include "Base/Map/SimpleMap.h"
#include "Generation/Map/Transformations/AreaTransformation.h"
#include "Base/Map/TransformedMap.h"
#include "Generation/Map/GenerationMap.h"


using namespace Steele;

/*

const Area AREA_2x2 = Area("**\n"	"**\n");
const Area AREA_3x2 = Area("***\n"	"***\n");
const Area AREA_2x3 = Area("**\n"	"**\n"	"**\n");


TEST(AreaTransformation__align__ZeroArea__NothingModified)
{
	auto a = Area::ZERO;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.align_to_area();
	
	
	ASSERT_FALSE(tm.is_transformed());
	ASSERT_IS(0, tm.transformation_stack().size());
}

TEST(AreaTransformation__align__AreaWithoutOffset__NothingModified)
{
	auto a = AREA_2x2;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.align_to_area();
	
	
	ASSERT_FALSE(tm.is_transformed());
	ASSERT_IS(0, tm.transformation_stack().size());
}

TEST(AreaTransformation__align__AreaWithOffset__AreaOffsetReset)
{
	auto a = AREA_2x2;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	a.set_offset(2, 3);
	
	
	t.align_to_area();
	
	
	ASSERT_IS(v2i_zero, a.offset());
}

TEST(AreaTransformation__align__AreaWithOffset__TransformationStackModified)
{
	auto a = AREA_2x2;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	a.set_offset(2, 3);
	
	
	t.align_to_area();
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(2, 3, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
}

TEST(AreaTransformation__align__AfterTransformation__TransformationAndAreaValuesCombinedCorrectly)
{
	auto a = AREA_2x2;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	a.set_offset(2, 3);
	t.add_transformation(1, 1);
	
	t.align_to_area();
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(2, 3, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
}


TEST(AreaTransformation__add_transformation__VectorOnly_AreaWithoutSize__TransformationAdded)
{
	auto a = Area::ZERO;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(2, 1, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__VectorOnly_AreaWithoutSize__AreaOffsetNotModified)
{
	auto a = Area::ZERO;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	
	
	ASSERT_IS(v2i_zero, a.offset());
}


TEST(AreaTransformation__add_transformation__VectorOnly_AreaAtZero__AreaOffsetModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	
	
	ASSERT_IS(v2i(-2, -1), a.offset());
}

TEST(AreaTransformation__add_transformation__VectorOnly_AreaAtZero__TransformationAdded)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(2, 1, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__Vector_Only_TransformationAlreadExist__TransformationModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	t.add_transformation(20, 10);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(22, 11, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
	
	ASSERT_IS(v2i(-22, -11), a.offset());
}

TEST(AreaTransformation__add_transformation__Vector_Only__OverloadsTest)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(2, 1);
	t.add_transformation(v2i(2, 1));
	t.add_transformation(Direction::North);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(4, 2, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
	ASSERT_IS(v2i(-4, -2), a.offset());
}

TEST(AreaTransformation__add_transformation__Vector_Only_AreaHasOffset__AreaOffsetModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	
	t.add_transformation(20, 10);
	
	
	ASSERT_IS(v2i(-18, -9), a.offset());
}

TEST(AreaTransformation__add_transformation__Vector_Only_AreaHasOffset__TransformationModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	
	t.add_transformation(20, 10);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(20, 10, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
}


TEST(AreaTransformation__add_transformation__Rotation_Only_ZeroArea__TransformationModifiedCorrectly)
{
	auto a = Area::ZERO;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::East);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i_zero, tm.transformation().Offset);
	ASSERT_IS(Direction::East, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__Rotation_East__TransformationModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::East);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(1, 0, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::East, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__Rotation_East__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::East);
	
	
	ASSERT_IS(v2i_zero, a.offset());
	ASSERT_IS(AREA_3x2, a);
}

TEST(AreaTransformation__add_transformation__Rotation_West__TransformationModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::West);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(0, 2, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::West, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__Rotation_West__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::West);
	
	
	ASSERT_IS(v2i_zero, a.offset());
	ASSERT_IS(AREA_3x2, a);
}

TEST(AreaTransformation__add_transformation__Rotation_South__TransformationModifiedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::South);
	
	
	ASSERT_TRUE(tm.is_transformed());
	ASSERT_IS(1, tm.transformation_stack().size());
	ASSERT_IS(v3i(1, 2, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::South, tm.transformation().Dir);
}

TEST(AreaTransformation__add_transformation__Rotation_South__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(Direction::South);
	
	
	ASSERT_IS(v2i_zero, a.offset());
	ASSERT_IS(AREA_2x3, a);
}


TEST(AreaTransformation__add_transformation__Rotation_East_AreaWithOffset__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	t.add_transformation(Direction::East);
	
	
	ASSERT_IS(v2i(2, 1), a.offset());
	ASSERT_IS(AREA_3x2, a.get_reset_offset_area());
}

TEST(AreaTransformation__add_transformation__Rotation_West_AreaWithOffset__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	t.add_transformation(Direction::West);
	
	
	ASSERT_IS(v2i(2, 1), a.offset());
	ASSERT_IS(AREA_3x2, a.get_reset_offset_area());
}

TEST(AreaTransformation__add_transformation__Rotation_South_AreaWithOffset__AreaModified)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	t.add_transformation(Direction::South);
	
	
	ASSERT_IS(v2i(2, 1), a.offset());
	ASSERT_IS(AREA_2x3, a.get_reset_offset_area());
}


TEST(AreaTransformation__add_transformation__Rotation_East_AreaWithOffset__TransformationCalculatedCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(10, 1);
	t.add_transformation(Direction::East);
	
	
	auto actualTransformation = tm.transformation();
	auto v_0 = actualTransformation.apply(v3i(10, 1, 2));
	auto v_2_3 = actualTransformation.apply(v3i(12, 4, 3));
	
	ASSERT_IS(v3i(11, 1, 2), v_0);
	ASSERT_IS(v3i(8, 3, 3), v_2_3);
}


TEST(AreaTransformation__transformation__SetCorrectly)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	t.add_transformation(v2i(2, 3), Direction::South);
	
	
	ASSERT_IS(t.transformation(), tm.transformation());
}


TEST(AreaTransformation__reset_transformation__SanityTest)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	
	a.set_offset(2, 1);
	t.add_transformation(20, 10);
	
	
	t.reset_transformation();
	
	
	ASSERT_FALSE(tm.is_transformed());
	ASSERT_IS(0, tm.transformation_stack().size());
	ASSERT_IS(v3i(0, 0, 0), tm.transformation().Offset);
	ASSERT_IS(Direction::North, tm.transformation().Dir);
	
	ASSERT_IS(v2i(2, 1), a.offset());
	ASSERT_IS(AREA_2x3, a.get_reset_offset_area());
}


TEST(AreaTransformation__rotation__AreaAtZero__SanityTest)
{
	auto a = AREA_2x3;
	auto tm = AbstractTransformable();
	auto t = AreaTransformation(&tm, &a);
	
	v3i result;
	Transformation trans;
	
	
	t.add_transformation(Direction::East);
	
	trans = t.transformation(); 
	result = trans.apply(v3i(0, 0, 0));
	ASSERT_IS(v3i(1, 0, 0), result);
}
*/

#pragma clang diagnostic pop
