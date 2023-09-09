#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "../../test_utils.h"


#include "Generation/Brushes/FillBrush.h"


using namespace Steele;


TEST(FillBrush__can_fill__return_true)
{
	FillBrush f;
	
	ASSERT_TRUE(f.can_fill(Area::ZERO));
}


TEST(FillBrush__set_ground_id)
{
	FillBrush f;
	
	
	f.set_palette_id(13);
	f.set_ground_id(12);
	
	
	ASSERT_IS(12, f.get_ground_id());
	ASSERT_IS(NULL_ID, f.get_palette_id());
	
	
	f.set_ground_id(14);
	
	
	ASSERT_IS(14, f.get_ground_id());
	ASSERT_IS(NULL_ID, f.get_palette_id());
}


TEST(FillBrush__set_palette_id)
{
	FillBrush f;
	
	
	f.set_ground_id(12);
	f.set_palette_id(13);
	
	
	ASSERT_IS(NULL_ID, f.get_ground_id());
	ASSERT_IS(13, f.get_palette_id());
	
	
	f.set_palette_id(15);
	
	
	ASSERT_IS(NULL_ID, f.get_ground_id());
	ASSERT_IS(15, f.get_palette_id());
}


TEST(FillBrush__direction_settings__passed_by_refernec)
{
	FillBrush f;
	
	
	f.direction_settings().ConstantDirection = Direction::West;
	auto dir = f.direction_settings().ConstantDirection;
	auto exp = Direction::West;
	
	ASSERT_IS(exp, dir);
	
	
	f.direction_settings().ConstantDirection = Direction::East;
	dir = f.direction_settings().ConstantDirection;
	exp = Direction::East;
	
	
	ASSERT_IS(exp, dir);
}


TEST(FillBrush__direction_settings__passed_by_value)
{
	FillBrush f;
	
	DirectionSettings a;
	
	
	a.ConstantDirection = Direction::West;
	f.set_direction_settings(a);
	
	auto dir = f.direction_settings().ConstantDirection;
	auto exp = Direction::West;
	
	ASSERT_IS(exp, dir);
	
	
	a.ConstantDirection = Direction::East;
	f.set_direction_settings(a);
	
	dir = f.direction_settings().ConstantDirection;
	exp = Direction::East;
	
	
	ASSERT_IS(exp, dir);
}


TEST(FillBrush__get_direction_settings)
{
	FillBrush f;
	
	DirectionSettings a;
	Direction o;
	
	o = f.get_direction_settings().ConstantDirection;
	a.ConstantDirection = o;
	a.ConstantDirection++;
	
	ASSERT_IS_NOT(a.ConstantDirection, f.get_direction_settings().ConstantDirection);
	ASSERT_IS(o, f.get_direction_settings().ConstantDirection);
}





#pragma clang diagnostic pop