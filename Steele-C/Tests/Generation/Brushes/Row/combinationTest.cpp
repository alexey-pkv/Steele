#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "Utils.h"
#include "../../../test_utils.h"


#include "Generation/Brushes/Row/combination.h"


using namespace std;

using namespace Steele;
using namespace Steele::combination;


TEST(reduce__Empty_Set_Passed__Empty_Set_Returned)
{
	set<int> a = {};
	
	reduce(a);
	
	ASSERT_IS(0, a.size());
}

TEST(reduce__Set_With_One_Element_Passed__Same_Set_Returned)
{
	set<int> a = { 5 };
	
	reduce(a);
	
	ASSERT_IS(1, a.size());
	ASSERT_TRUE(contains(a, 5));
}

TEST(reduce__Set_With_Unique_Values__Values_Not_Removed)
{
	set<int> a = { 5, 21, 13, 11 };
	set<int> b = a;
	
	reduce(a);
	
	ASSERT_IS(b.size(), a.size());
	ASSERT_IS(a, b);
}

TEST(reduce__Set_With_Similar_Values__Similar_Values_Removed)
{
	set<int> a = { 5, 26, 21, 13, 11, 10, 26 };
	set<int> b = { 5,     21, 13, 11,        };
	
	reduce(a);
	
	ASSERT_IS(a, b);
}

TEST(reduce__Set_With_One__Only_One_Remains)
{
	set<int> a = { 5, 26, 21, 13, 1, 11, 10, 26 };
	set<int> b = { 1 };
	
	reduce(a);
	
	ASSERT_IS(a, b);
}


TEST(to_combination_set__Empty_Set__No_Errors)
{
	set<int>	a		= {};
	int 		target	= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_TRUE(a.empty());
}

TEST(to_combination_set__All_Values_Are_Bigger__Retrun_Empty_Set)
{
	set<int>	a		= { 20, 30, 15, 129 };
	int 		target	= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_TRUE(a.empty());
}

TEST(to_combination_set__Same_Value_Exists__Retun_Value)
{
	set<int>	a			= { 10 };
	set<int>	expected	= { 10 };
	int 		target		= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__All_Numbers_Are_Dividers__Retrun_All_Valid_Values)
{
	set<int>	a			= { 2, 10, 5 };
	set<int>	expected	= { 2, 10, 5 };
	int 		target		= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Negatives_And_Zero_Exists__Negatives_Removed)
{
	set<int>	a			= { -2, 10, 5, 0 };
	set<int>	expected	= { 10, 5 };
	int 		target		= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Numbers_That_Are_Not_Dividers_Exists__Values_Remain)
{
	set<int>	a			= { 3, 11, 5, 2 };
	set<int>	expected	= { 3, 5, 2 };  	// 10 - 3 = 7 = 5 + 2
	int 		target		= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__One_Exists__All_Numbers_Stay)
{
	set<int>	a			= { 1, 3, 9, 6, 8 };
	set<int>	expected	= { 1, 3, 9, 6, 8 };
	int 		target		= 10;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Numbers_That_Can_Not_Be_Used_Are_Removed)
{
	set<int>	a			= { 10, 31, 16, 99 };
	set<int>	expected	= { 10, 16 };
	int 		target		= 100;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Complex_Case_Sanity_Test__Valid_Numbers)
{
	set<int>	a			= { 10001, 1002 };
	set<int>	expected	= { 10001, 1002 };
	int 		target		= 10001 * 1002 + 1;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Complex_Case_Sanity_Test__Not_Possiable)
{
	set<int>	a			= { 3, 300, 9 };
	set<int>	expected	= { };
	int 		target		= 300 + 1;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}

TEST(to_combination_set__Perfermance_Test_With_1)
{
	set<int>	a			= { 3, 300, 9, 1 };
	set<int>	expected	= { 3, 300, 9, 1 };
	int 		target		= 3 * 1000 * 1000 + 1;
	
	
	to_combination_set(target, a);
	
	
	ASSERT_IS(expected, a);
}




#pragma clang diagnostic pop