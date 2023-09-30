#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "test_utils.h"


#include "DataTypes/Transformation.h"
#include "DataTypes/Types.h"


using namespace Steele;


TEST(Transformation__Zero__No_Changes)
{
	Transformation t = Transformation::ZERO;
	
	ASSERT_IS(v3i_zero,			t.apply(v3i_zero));
	ASSERT_IS(v3i_one,			t.apply(v3i_one));
	ASSERT_IS(v3i_x_one,		t.apply(v3i_x_one));
	ASSERT_IS(v3i_y_one,		t.apply(v3i_y_one));
	ASSERT_IS(v3i_z_one,		t.apply(v3i_z_one));
	ASSERT_IS(v3i(5, 6, 7),		t.apply(v3i(5, 6, 7)));
	ASSERT_IS(v3i(5, -6, 7),	t.apply(v3i(5, -6, 7)));
}

TEST(Transformation__Rotation_Only__East)
{
	Transformation t(Direction::East);
	
	ASSERT_IS(v3i_zero,			t.apply(v3i_zero));
	ASSERT_IS(v3i(1, -1, 1),	t.apply(v3i_one));
	
	ASSERT_IS(-v3i_y_one,		t.apply(v3i_x_one));
	ASSERT_IS(v3i_x_one,		t.apply(v3i_y_one));
	ASSERT_IS(v3i_z_one,		t.apply(v3i_z_one));
	
	ASSERT_IS(v3i(5, -1, 6),	t.apply(v3i(1, 5, 6)));
	ASSERT_IS(v3i(-5, 1, 6),	t.apply(v3i(-1, -5, 6)));
}

TEST(Transformation__Rotation_Only__South)
{
	Transformation t(Direction::South);
	
	ASSERT_IS(v3i_zero,			t.apply(v3i_zero));
	ASSERT_IS(v3i(-1, -1, 1),	t.apply(v3i_one));
	
	ASSERT_IS(-v3i_x_one,		t.apply(v3i_x_one));
	ASSERT_IS(-v3i_y_one,		t.apply(v3i_y_one));
	ASSERT_IS(v3i_z_one,		t.apply(v3i_z_one));
	
	ASSERT_IS(v3i(-1, -5, 6),	t.apply(v3i(1, 5, 6)));
	ASSERT_IS(v3i(1, 5, 6),		t.apply(v3i(-1, -5, 6)));
}

TEST(Transformation__Rotation_Only__West)
{
	Transformation t(Direction::West);
	
	ASSERT_IS(v3i_zero,			t.apply(v3i_zero));
	ASSERT_IS(v3i(-1, 1, 1),	t.apply(v3i_one));
	
	ASSERT_IS(v3i_y_one,		t.apply(v3i_x_one));
	ASSERT_IS(-v3i_x_one,		t.apply(v3i_y_one));
	ASSERT_IS(v3i_z_one,		t.apply(v3i_z_one));
	
	ASSERT_IS(v3i(-5, 1, 6),	t.apply(v3i(1, 5, 6)));
	ASSERT_IS(v3i(5, -1, 6),	t.apply(v3i(-1, -5, 6)));
}

TEST(Transformation__Offset)
{
	Transformation t(v3i(5, -6, 7));
	
	ASSERT_IS(v3i(5, -6, 7),	t.apply(v3i_zero));
	ASSERT_IS(v3i(6, -5, 8),	t.apply(v3i_one));
	
	ASSERT_IS(v3i(6, -6, 7),	t.apply(v3i_x_one));
	ASSERT_IS(v3i(5, -5, 7),	t.apply(v3i_y_one));
	ASSERT_IS(v3i(5, -6, 8),	t.apply(v3i_z_one));
	
	ASSERT_IS(v3i(5, -6, 7) + v3i(1, 5, 6),		t.apply(v3i(1, 5, 6)));
	ASSERT_IS(v3i(5, -6, 7) + v3i(-1, -5, 6),	t.apply(v3i(-1, -5, 6)));
}

TEST(Transformation__Offset_With_Rotation)
{
	Transformation t(v3i(5, -6, 7), Direction::South);
	
	ASSERT_IS(v3i(5, -6, 7),	t.apply(v3i_zero));
	ASSERT_IS(v3i(4, -7, 8),	t.apply(v3i_one));
	
	ASSERT_IS(v3i(4, -6, 7),	t.apply(v3i_x_one));
	ASSERT_IS(v3i(5, -7, 7),	t.apply(v3i_y_one));
	ASSERT_IS(v3i(5, -6, 8),	t.apply(v3i_z_one));
	
	ASSERT_IS(v3i(5, -6, 7) + v3i(-1, -5, 6),	t.apply(v3i(1, 5, 6)));
	ASSERT_IS(v3i(5, -6, 7) + v3i(1, 5, 6),		t.apply(v3i(-1, -5, 6)));
}

TEST(Transformation__EqualSign)
{
	Transformation d_s(Direction::South);
	Transformation d_n(Direction::North);
	
	Transformation d_100(v3i_x_one);
	Transformation d_010(v3i_y_one);
	
	Transformation d_s_copy(d_s);
	Transformation d_100_copy(d_100);
	
	
	ASSERT_TRUE(Transformation::ZERO == Transformation::ZERO);
	ASSERT_FALSE(Transformation::ZERO != Transformation::ZERO);
	
	ASSERT_TRUE(d_s == d_s);
	ASSERT_FALSE(d_s != d_s);
	ASSERT_FALSE(d_s == d_n);
	ASSERT_TRUE(d_s != d_n);
	ASSERT_TRUE(d_s == d_s_copy);
	ASSERT_FALSE(d_s != d_s_copy);
	
	ASSERT_TRUE(d_100 == d_100);
	ASSERT_FALSE(d_100 != d_100);
	ASSERT_FALSE(d_100 == d_010);
	ASSERT_TRUE(d_100 != d_010);
	ASSERT_TRUE(d_100 == d_100_copy);
	ASSERT_FALSE(d_100 != d_100_copy);
}

TEST(Transformation__Modify__Zero_By_Zero__No_Change)
{
	ASSERT_IS(Transformation::ZERO, Transformation::ZERO + Transformation::ZERO);
	ASSERT_IS(Transformation::ZERO, Transformation::ZERO - Transformation::ZERO);
}

TEST(Transformation__Modify__Offset_Only)
{
	Transformation a(v3i { 2, 5, 6 });
	Transformation b(v3i { -1, 12, 3 });
	
	Transformation sum(v3i { 1, 17, 9 });
	Transformation sub(v3i { 3, -7, 3 });
	
	ASSERT_IS(sum, a + b);
	ASSERT_IS(sub, a - b);
}

TEST(Transformation__Modify__Rotation_Only)
{
	Transformation a(Direction::West);
	Transformation b(Direction::South);
	Transformation c(Direction::East);
	Transformation sum_ab(Direction::East);
	Transformation sub_ab(Direction::East);
	Transformation sum_ac(Direction::North);
	Transformation sub_ac(Direction::South);
	
	
	ASSERT_IS(sum_ab, a + b);
	ASSERT_IS(sub_ab, a - b);
	
	ASSERT_IS(sum_ac, a + c);
	ASSERT_IS(sub_ac, a - c);
}

TEST(Transformation__Modify__Transformations_Combined_Correctly)
{
	Transformation a({ 3, -5, 6 }, Direction::West);
	Transformation b({ 2, -6, 1 }, Direction::South);
	Transformation c({ -1, 2, -2 }, Direction::East);
	
	Transformation sum_ab({ 9, -3, 7 }, Direction::East);
	Transformation sum_abc = sum_ab + c;
	
	
	ASSERT_IS(sum_ab, a + b);
	ASSERT_IS(a, sum_ab - b);
	
	ASSERT_IS(sum_abc, sum_ab + c);
	ASSERT_IS(sum_ab, sum_abc - c);
	
	ASSERT_IS(a, (sum_abc - c) - b);
}

TEST(Transformation__Modify__Sanity)
{
	Transformation a({ 3, -5, 6 }, Direction::West);
	Transformation b({ 2, -6, 2 }, Direction::South);
	
	ASSERT_IS(v3i(10, -4, 9),	(a + b).apply(v3i_one));
	ASSERT_IS(v3i(10, -4, 5),	(a - b).apply(v3i_one));
}

TEST(Transformation__Modify_By_Vector__Sanity)
{
	Transformation	a({ 3, -5, 6 }, Direction::West);
	v3i				b(2, -6, 2);
	
	ASSERT_IS(v3i(8, -2, 9),	(a + b).apply(v3i_one));
	ASSERT_IS(v3i(-4, -6, 5),	(a - b).apply(v3i_one));
}

TEST(Transformation__Modify__Symetry)
{
	Transformation a({ 3, -5, 6 }, Direction::West);
	Transformation b({ 2, -6, 0 }, Direction::South);
	Transformation c({ -1, 2, -2 }, Direction::East);
	
	ASSERT_IS(a - a, Transformation::ZERO);
	ASSERT_IS(Transformation::ZERO, a + (Transformation::ZERO - a));
	
	ASSERT_IS((a + b) - b, a);
	ASSERT_IS(((a + b) + c) - c, a + b);
	ASSERT_IS((((a + b) + c) - c) - b, a);
}


#pragma clang diagnostic pop
