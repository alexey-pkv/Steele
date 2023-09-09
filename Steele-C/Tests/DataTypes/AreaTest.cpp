#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "test_utils.h"


#include "DataTypes/Area.h"


using namespace Steele;


void assert_contains(const Area& small, const Area& big)
{
	ASSERT_TRUE(small <= big);
	ASSERT_TRUE(big >= small);
	
	if (small == big)
	{
		ASSERT_TRUE(small >= big);
		ASSERT_TRUE(big <= small);
		
		ASSERT_FALSE(small < big);
		ASSERT_FALSE(small > big);
		
		ASSERT_FALSE(big < small);
		ASSERT_FALSE(big > small);
	}
	else
	{
		ASSERT_FALSE(small >= big);
		ASSERT_FALSE(big <= small);
		
		ASSERT_TRUE(small < big);
		ASSERT_TRUE(big > small);
		
		ASSERT_FALSE(small > big);
		ASSERT_FALSE(big < small);
	}
}

void assert_not_contains_both(const Area& a, const Area& b)
{
	ASSERT_FALSE(a <= b);
	ASSERT_FALSE(a >= b);
	ASSERT_FALSE(a < b);
	ASSERT_FALSE(a > b);
	
	ASSERT_FALSE(b <= a);
	ASSERT_FALSE(b >= a);
	ASSERT_FALSE(b < a);
	ASSERT_FALSE(b > a);
}

void assert_area_equals(const Area& a, const string& expected)
{
	ASSERT_IS(a, Area{expected});
}

void assert_or(const Area& a, const Area& b, const Area& expected)
{
	ASSERT_IS(a | b, b | a);
	ASSERT_IS(expected, a | b);
	ASSERT_IS(expected, (Area(a) |= b));
	ASSERT_IS(expected, (Area(b) |= a));
}

void assert_sub(const Area& a, const Area& b, const Area& expected)
{
	ASSERT_IS(expected, a - b);
	ASSERT_IS(expected, (Area(a) -= b));
}

void assert_sub(const string& a, const string& b, const string& expected)
{
	assert_sub(Area { a }, Area { b }, Area { expected });
}


void assert_or(const string& a, const string& b, const string& expected)
{
	assert_or(Area { a }, Area { b }, Area { expected });
}

void assert_and(const Area& a, const Area& b, const Area& expected)
{
	ASSERT_IS(a & b, b & a);
	ASSERT_IS(expected, a & b);
	ASSERT_IS(expected, (Area(a) &= b));
	ASSERT_IS(expected, (Area(b) &= a));
}

void assert_and(const string& a, const string& b, const string& expected)
{
	assert_and(Area { a }, Area { b }, Area { expected });
}

void assert_overlap(const Area& a, const Area&b, bool expected)
{
	ASSERT_IS(expected, a.overlaps(b));
	ASSERT_IS(expected, b.overlaps(a));
}


TEST(Area__GetArea__EmptyArea__AreaIsZero)
{
	ASSERT_IS(Area().get_area(), 0);
	ASSERT_IS(Area(Rect2i(0, 0, 0, 0)).get_area(), 0);
}

TEST(Area__GetArea__NotEmpty__AreaCalculatedCorrectly)
{
	ASSERT_IS(Area(Rect2i(0, 0, 1, 1)).get_area(), 1);
	ASSERT_IS(Area(Rect2i(0, 0, 5, 1)).get_area(), 5);
	ASSERT_IS(Area(Rect2i(0, 0, 1, 5)).get_area(), 5);
	ASSERT_IS(Area(Rect2i(0, 0, 5, 5)).get_area(), 25);
	
	ASSERT_IS(Area(Rect2i(0, 0, 5, 6)).get_area(), 30);
	ASSERT_IS(Area(Rect2i(0, 0, 7, 5)).get_area(), 35);
	
	ASSERT_IS(Area(Rect2i(1, 2, 5, 6)).get_area(), 30);
	ASSERT_IS(Area(Rect2i(2, 1, 7, 5)).get_area(), 35);
}


TEST(Area__Copy__Constructor)
{
	Area a(Rect2i(0, 0, 2, 2));
	Area b(a); // NOLINT(*-unnecessary-copy-initialization)
	
	ASSERT_IS(a, b);
	ASSERT_IS(a, Area(Rect2i(0, 0, 2, 2)));
	ASSERT_IS(b, Area(Rect2i(0, 0, 2, 2)));
}

TEST(Area__EQUAL__SIGN)
{
	ASSERT(Area() == Area(Rect2i(0, 0, 0, 0)));
	ASSERT_NOT(Area() != Area(Rect2i(0, 0, 0, 0)));
	
	auto a = Area(Rect2i(0, 0, 1, 1));
	auto b = Area(Rect2i(0, 0, 1, 1));
	auto c = Area(Rect2i(0, 0, 2, 1));
	auto d = Area(Rect2i(0, 0, 1, 2));
	
	ASSERT		(a == b);
	ASSERT_NOT	(a != b);
	ASSERT		(a != c);
	ASSERT_NOT	(a == c);
	ASSERT		(a != d);
	ASSERT_NOT	(a == d);
	
	a += v2i(1, 1);
	
	ASSERT		(a != b);
	ASSERT_NOT	(a == b);
	ASSERT		(a != c);
	ASSERT_NOT	(a == c);
	ASSERT		(a != d);
	ASSERT_NOT	(a == d);
	
	a.set_offset({0, 0});
	
	a += v2i (3, 2);
	b += v2i (3, 2);
	
	ASSERT		(a == b);
	ASSERT_NOT	(a != b);
	ASSERT		(a != c);
	ASSERT_NOT	(a == c);
	ASSERT		(a != d);
	ASSERT_NOT	(a == d);
}


TEST(Area__Or__WithEmptyArea)
{
	Area a = Area(Rect2i(3, 7, 1, 1));
	
	assert_or(a, Area(), Area(a));
}

TEST(Area__Or__WithSelf)
{
	Area a = Area(Rect2i(3, 7, 1, 1));
	
	assert_or(a, Area(a), a);
	assert_or(Area(), Area(), Area());
}

TEST(Area__Or__Basic)
{
	assert_or(
		Area(Rect2i(0, 0, 1, 1)),
		Area(Rect2i(1, 0, 1, 1)),
		Area(Rect2i(0, 0, 2, 1)));
	
	assert_or(
		Area(Rect2i(0, 0, 1, 1)),
		Area(Rect2i(0, 1, 1, 1)),
		Area(Rect2i(0, 0, 1, 2)));
}

TEST(Area__And__WithEmptyArea)
{
	Area a = Area(Rect2i(3, 7, 1, 1));
	
	assert_and(a, Area(), Area());
}

TEST(Area__And__WithSelf)
{
	Area a = Area(Rect2i(3, 7, 1, 1));
	
	assert_and(a, Area(a), Area(a));
	assert_and(Area(), Area(), Area());
}

TEST(Area__And__Basic)
{
	assert_and(
		Area(Rect2i(0, 0, 2, 1)),
		Area(Rect2i(1, 0, 1, 1)),
		Area(Rect2i(1, 0, 1, 1)));
	
	assert_and(
		Area(Rect2i(0, 0, 1, 2)),
		Area(Rect2i(0, 1, 1, 1)),
		Area(Rect2i(0, 1, 1, 1)));
	
	assert_and(
		Area { 0, 0, 2, 2 },
		Area { 0, 0, 1, 1 },
		Area { 0, 0, 1, 1 });
	
	assert_and(
		Area { 0, 0, 2, 2 },
		Area { 0, 0, 1, 2 },
		Area { 0, 0, 1, 2 });
	
	assert_and(
		Area { 0, 0, 2, 2 },
		Area ( 0, 0, 2, 1 ),
		Area ( 0, 0, 2, 1 ));
	
	assert_and(
		Area { 0, 0, 2, 2 },
		Area { 0, 1, 1, 1 },
		Area { 0, 1, 1, 1 });
	
	assert_and(
		Area { 0, 0, 2, 2 },
		Area { 1, 0, 1, 1 },
		Area { 1, 0, 1, 1 });
	
	assert_and(
		Area { 0, 0, 3, 3 },
		Area { 1, 1, 1, 1 },
		Area { 1, 1, 1, 1 });
}

TEST(Area__And__NoCommonPoints)
{
	assert_and(
		Area { 0, 0, 2, 2 },
		Area { 3, 3, 2, 2 },
		Area ());
	
	assert_and(
		Area { -6, -6, 2, 2 },
		Area { 3, 3, 1, 1 },
		Area ());
}

TEST(Area__And__SimpleOverlap)
{
	assert_and(
		Area { 0, 0, 1, 1 },
		Area { 1, 1, 2, 2 },
		Area { 1, 1, 1, 1 });
}

TEST(Area__Contructor_FromTemplate)
{
	auto str = string {
		"*.**\n"
		"...*\n"
		"**..\n"
		"**.*\n"
	};
	
	assert_area_equals(Area { str }, str);
}


TEST(Area__Or__Complex_With_Volume)
{
	Area a = { 0, 0, 1, 1 };
	Area b = { 2, 2, 3, 3 };
	Area c = { 1, 1, 2, 2 };
	
	assert_area_equals(
		c | a | b,
		"..**\n"
		".***\n"
		"***.\n"
		"**..\n");
	
	assert_area_equals(
		b | c | a,
		"..**\n"
		".***\n"
		"***.\n"
		"**..\n");
}


TEST(Area__Or__Complex_FromTemplates)
{
	assert_or("*\n", "*\n", "*\n");
	
	assert_or(
		".*\n",
		"*.\n",
		"**\n");
	
	assert_or(
		"*\n"
		".\n",
		
		".\n"
		"*\n",
		
		"*\n"
		"*\n");
	
	assert_or(
		"..*\n",
		"*..\n",
		"*.*\n");
	
	assert_or(
		"*\n"
		".\n"
		".\n",
		
		".\n"
		".\n"
		"*\n",
		
		"*\n"
		".\n"
		"*\n");
	
	assert_or(
		"*\n"
		"*\n",
		
		"*\n"
		"*\n"
		".\n"
		".\n",
		
		"*\n"
		"*\n"
		"*\n"
		"*\n");
	
	assert_or(
		"*\n"
		"*\n",
		
		"*\n"
		"*\n"
		".\n",
		
		"*\n"
		"*\n"
		"*\n");
	
	assert_or(
		"*\n"
		"*\n",
		
		"*\n"
		"*\n",
		
		"*\n"
		"*\n");
	
	assert_or(
		"*\n"
		"*\n",
		
		"*\n"
		"*\n"
		".\n"
		".\n"
		".\n"
		".\n",
		
		"*\n"
		"*\n"
		".\n"
		".\n"
		"*\n"
		"*\n");
	
	assert_or(
		".**\n",
		"**\n",
		"***\n");
	
	assert_or(
		"..**\n",
		"**\n",
		"****\n");
	
	assert_or(
		"...**\n",
		"**\n",
		"**.**\n");
	
	assert_or(
		"....**\n",
		"**\n",
		"**..**\n");
	
	assert_or(
		"**..**..**\n"
		"**..**..**\n"
		"..**....**\n"
		"..**....**\n"
		"..**.....*\n",
		
		"..**....**\n"
		"..**....**\n"
		"**..**..**\n"
		"**..**..**\n"
		"**..**...*\n",
		
		"******..**\n"
		"******..**\n"
		"******..**\n"
		"******..**\n"
		"******...*\n");
}


TEST(Area__And__Complex_FromTemplates)
{
	assert_and("*\n", "*\n", "*\n");
	
	assert_and(
		"..**\n",
		"**\n",
		"");
	
	assert_and(
		".**\n",
		
		"**\n",
		
		".*\n");
	
	assert_and(
		"***\n",
		
		"**\n",
		
		"**\n");
	
	assert_and(
		"*.*\n",
		
		"**\n",
		
		"*\n");
	
	assert_and(
		"**..**..**\n"
		"**..**..**\n"
		"..**....**\n"
		"..**.....*\n"
		"..**.....*\n",
		
		"..**......\n"
		"******..**\n"
		"******..**\n"
		"**..**...*\n"
		"**..**..*.\n",
		
		"**..**..**\n"
		"..**....**\n"
		".........*\n"
		"..........\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"****\n"
		"****\n"
		"****\n",
		
		"****\n"
		"****\n"
		"****\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"......****\n"
		"......****\n"
		"......****\n"
		"..........\n"
		"..........\n",
		
		"......****\n"
		"......****\n"
		"......****\n"
		"..........\n"
		"..........\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"......****\n"
		"......****\n"
		"......****\n",
		
		"......****\n"
		"......****\n"
		"......****\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"****......\n"
		"****......\n"
		"****......\n"
		"..........\n"
		"..........\n",
		
		"****......\n"
		"****......\n"
		"****......\n"
		"..........\n"
		"..........\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..****....\n"
		"..****....\n"
		"..........\n",
		
		"..****....\n"
		"..****....\n"
		"..****....\n"
		"..........\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..*..*....\n"
		"..****....\n"
		"..........\n",
		
		"..****....\n"
		"..*..*....\n"
		"..****....\n"
		"..........\n");
	
	assert_and(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..*..*.**.\n"
		"..****....\n"
		"....***...\n",
		
		"..****....\n"
		"..*..*.**.\n"
		"..****....\n"
		"....***...\n");
	
	assert_and(
		"..........\n"
		"..........\n"
		"....******\n"
		"....******\n"
		"....******\n",
		
		"******....\n"
		"******....\n"
		"******....\n"
		"..........\n"
		"..........\n",
		
		"..........\n"
		"..........\n"
		"....**....\n"
		"..........\n"
		"..........\n");
}


TEST(Area__Sub__EmptyCases)
{
	assert_sub(".\n", "*\n", ".\n");
	assert_sub(".\n", "**\n**\n", ".\n");
	assert_sub("*\n", ".\n", "*\n");
	assert_sub(".\n", ".\n", ".\n");
	assert_sub("*\n", "*\n", ".\n");
	
	assert_sub(
		"...\n"
		"...\n"
		"...\n",
		
		"***\n"
		"*.*\n"
		"***\n",
		
		"...\n"
		"...\n"
		"...\n");
	
	assert_sub(
		"***\n"
		"*.*\n"
		"***\n",
		
		"...\n"
		"...\n"
		"...\n",
		
		"***\n"
		"*.*\n"
		"***\n");
}

TEST(Area__Sub__Complex)
{
	assert_sub(
		"..........\n"
		"..........\n"
		"....******\n"
		"....******\n"
		"....******\n",
		
		"******....\n"
		"******....\n"
		"******....\n"
		"..........\n"
		"..........\n",
		
		"..........\n"
		"..........\n"
		"......****\n"
		"....******\n"
		"....******\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"......****\n"
		"......****\n"
		"......****\n"
		"..........\n"
		"..........\n",
		
		"******....\n"
		"******....\n"
		"******....\n"
		"**********\n"
		"**********\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"......****\n"
		"......****\n"
		"......****\n",
		
		"**********\n"
		"**********\n"
		"******....\n"
		"******....\n"
		"******....\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"****......\n"
		"****......\n"
		"****......\n"
		"..........\n"
		"..........\n",
		
		"....******\n"
		"....******\n"
		"....******\n"
		"**********\n"
		"**********\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..****....\n"
		"..****....\n"
		"..........\n",
		
		"**********\n"
		"**....****\n"
		"**....****\n"
		"**....****\n"
		"**********\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..*..*....\n"
		"..****....\n"
		"..........\n",
		
		"**********\n"
		"**....****\n"
		"**.**.****\n"
		"**....****\n"
		"**********\n");
	
	assert_sub(
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n"
		"**********\n",
		
		"..****....\n"
		"..*..*.**.\n"
		"..****....\n"
		"....***...\n",
		
		"**********\n"
		"**....****\n"
		"**.**.*..*\n"
		"**....****\n"
		"****...***\n");
}


TEST(Area__Rotate__Empty)
{
	Area a = Area ();
	
	ASSERT_IS(Area {}, a * Direction::North);
	ASSERT_IS(Area {}, a * Direction::East);
	ASSERT_IS(Area {}, a * Direction::South);
	ASSERT_IS(Area {}, a * Direction::West);
}


TEST(Area__Rotate__Single)
{
	Area a = Area { 
		".*\n"
		"..\n"
	};
	
	Area original = Area(a);
	
	ASSERT_IS(original, a * Direction::North);
	ASSERT_IS(original, a * Direction::East);
	ASSERT_IS(original, a * Direction::South);
	ASSERT_IS(original, a * Direction::West);
	
	a = Area { 
		"*\n"
	};
	
	original = Area(a);
	
	ASSERT_IS(original, a * Direction::North);
	ASSERT_IS(original, a * Direction::East);
	ASSERT_IS(original, a * Direction::South);
	ASSERT_IS(original, a * Direction::West);
}


TEST(Area__Rotate__NoOffset)
{
	Area h = Area { 
		"**\n"
	};
	
	Area v = Area { 
		"*\n" 
		"*\n"
	};
	
	Area original_h = Area(h);
	Area original_v = Area(v);
	
	ASSERT_IS(original_h, h * Direction::North);
	ASSERT_IS(original_h, h * Direction::South);
	ASSERT_IS(original_h, v * Direction::East);
	ASSERT_IS(original_h, v * Direction::West);
	
	ASSERT_IS(original_v, v * Direction::North);
	ASSERT_IS(original_v, v * Direction::South);
	ASSERT_IS(original_v, h * Direction::East);
	ASSERT_IS(original_v, h * Direction::West);
}


TEST(Area__Rotate)
{
	Area a = Area { 
		".**.\n"
		".*..\n"
		".*..\n"
		"....\n"
		"....\n"
	};
	
	auto n = a * Direction::North;
	auto e = a * Direction::East;
	auto s = a * Direction::South;
	auto w = a * Direction::West;
	
	ASSERT_IS(n ,a);
	
	Area nnn = Area (
		"....\n"
		".***\n"
		"...*\n"
		"....\n"
		"....\n");
	
	assert_area_equals(e, 
		"....\n"
		".***\n"
		"...*\n"
		"....\n"
		"....\n");
	
	assert_area_equals(s, 
		"..*.\n"
		"..*.\n"
		".**.\n"
		"....\n"
		"....\n");
	
	assert_area_equals(w, 
		"....\n"
		".*..\n"
		".***\n"
		"....\n"
		"....\n");
}


TEST(Area__ForEach)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a)
{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 1, 2 },
		{ 1, 3 },
		{ 2, 1 },
		{ 2, 2 },
		{ 3, 2 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach_Revers)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a)
{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 1, 2 },
		{ 1, 3 },
		{ 2, 1 },
		{ 2, 2 },
		{ 3, 2 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Bottom)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_bottom()) 
	{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 1, 2 },
		{ 2, 1 },
		{ 3, 2 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Reverse_Bottom)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_r_bottom())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 3, 2 },
		{ 2, 1 },
		{ 1, 2 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Top)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_top())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 1, 3 },
		{ 2, 2 },
		{ 3, 2 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Reverse_Top)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_r_top())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 3, 2 },
		{ 2, 2 },
		{ 1, 3 }
	};
	
	ASSERT_IS(expected, result);
}


TEST(Area__ForEach__Left)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_left())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected =  {
		{ 2, 1 },
		{ 1, 2 },
		{ 1, 3 }
	};
	
	ASSERT_IS(expected, result);
}


TEST(Area__ForEach__Reverse_Left)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_r_left())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected =  {
		{ 1, 3 },
		{ 1, 2 },
		{ 2, 1 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Right)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_right())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected =  {
		{ 2, 1 },
		{ 3, 2 },
		{ 1, 3 } 
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Reverse_Right)
{
	Area a = Area(
		"....\n"
		".*..\n"
		".***\n"
		"..*.\n"
		"....\n"
	); 
	
	vector<v2i> result;
	
	for (auto v : a.iterate_r_right())
	{
		result.push_back(v);
	}
	
	vector<v2i> expected = {
		{ 1, 3 },
		{ 3, 2 },
		{ 2, 1 }
	};
	
	ASSERT_IS(expected, result);
}

TEST(Area__ForEach__Empty)
{
	Area a = Area(); 
	
	
	for (auto v : a) { ASSERT(false); }
	
	for (auto v : a.iterate_r_top()) 		{ ASSERT(false); }
	for (auto v : a.iterate_r_bottom()) 	{ ASSERT(false); }
	for (auto v : a.iterate_r_left()) 		{ ASSERT(false); }
	for (auto v : a.iterate_r_right()) 		{ ASSERT(false); }
	
	for (auto v : a.iterate_top()) 		{ ASSERT(false); }
	for (auto v : a.iterate_bottom()) 	{ ASSERT(false); }
	for (auto v : a.iterate_left()) 	{ ASSERT(false); }
	for (auto v : a.iterate_right()) 	{ ASSERT(false); }
}

TEST(Area__ForEach__SingleItem)
{
	int count;
	Area a = Area(
		".*\n"
		"..\n"
		"..\n"
	);
	
	count = 0; for (auto v : a) { ASSERT(v == v2i(1, 2) && count++ == 0); }
	
	count = 0; for (auto v : a.iterate_r_top()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_r_bottom()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_r_left()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_r_right()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	
	count = 0; for (auto v : a.iterate_top()) 		{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_bottom()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_left()) 		{ ASSERT(v == v2i(1, 2) && count++ == 0); }
	count = 0; for (auto v : a.iterate_right()) 	{ ASSERT(v == v2i(1, 2) && count++ == 0); }
}

TEST(Area__Contains__Vector)
{
	Area a = Area(
		"....\n"
		".*..\n"
		"..**\n"
		"..*.\n"
		"....\n"
	); 
	
	
	ASSERT_FALSE(a[v2i(-2, -2)]);
	ASSERT_FALSE(a[v2i(20, 20)]);
	ASSERT_FALSE(a[v2i(4, 4)]);
	ASSERT_FALSE(a[v2i(4, 2)]);
	ASSERT_FALSE(a[v2i(2, 4)]);
	
	ASSERT_FALSE(a[v2i(0, 0)]);
	ASSERT_FALSE(a[v2i(0, 1)]);
	ASSERT_FALSE(a[v2i(1, 0)]);
	
	ASSERT_FALSE(a[v2i(1, 2)]);
	ASSERT_FALSE(a[v2i(3, 1)]);
	ASSERT_FALSE(a[v2i(1, 1)]);
	ASSERT_FALSE(a[v2i(2, 0)]);
	ASSERT_TRUE(a[v2i(2, 1)]);
	
	
	ASSERT_FALSE(a[v2i(2, 1) - v2i(5, 5)]);
	
	a -= v2i(5, 5);
	
	ASSERT_FALSE(a[v2i(2, 1)]);
	ASSERT_TRUE(a[v2i(2, 1) - v2i(5, 5)]);
}


TEST(Area__Overlap__WithEmpty)
{
	assert_overlap(Area(), Area(), false);
	assert_overlap(Area("*\n"), Area(), false);
}

TEST(Area__Overlap__Basic)
{
	assert_overlap(Area("*\n"), Area("*\n"), true);
}

TEST(Area__Overlap__WithOffset)
{
	assert_overlap(
		Area("*\n"),
		Area(
			"*\n"
			".\n"
		),
		false);
	
	assert_overlap(
		Area("*\n"),
		Area(
			".*\n"
		),
		false);
	
	assert_overlap(
		Area(
			"**\n"
			"**\n"
		),
		Area(
			"..**\n"
			"..**\n"
			"....\n"
			"....\n"
		),
		false);
}

TEST(Area__Overlap)
{
	auto main = Area(
		"...******..\n"
		"...******..\n"
		"...**..**..\n"
		"...**..**..\n"
		"...******..\n"
		"...******..\n"
		"...........\n"
		"...........\n"
	);
	
	assert_overlap(
		main,
		Area(
			"..***..***.\n"
			"..*......*.\n"
			"...........\n"
			"..*..**..*.\n"
			"..*..**..*.\n"
			"...........\n"
			"..*......*.\n"
			"..**...***.\n"
			"...........\n"
		),
		false);
	
	assert_overlap(
		main,
		Area(
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...*.......\n"
			"...........\n"
			"...........\n"
		),
		true);
	
	assert_overlap(
		main,
		Area(
			"........*..\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
		),
		true);
	
	assert_overlap(
		main,
		Area(
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"........*..\n"
			"...........\n"
			"...........\n"
		),
		true);
	
	assert_overlap(
		main,
		Area(
			"...*.......\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
		),
		true);
}


TEST(Area__Contains__Empty)
{
	assert_contains(Area(), Area());
	assert_contains(Area(), Area("*\n"));
}

TEST(Area__Contains__Equal)
{
	assert_contains(Area("*\n"), Area("*\n"));
}

TEST(Area__Contains__WithOffset)
{
	assert_not_contains_both(Area(".*\n"), Area("*\n"));
	
	assert_not_contains_both(
		Area(
			"*\n"
			".\n"
		),
		Area("*\n"));
	
	assert_not_contains_both(
		Area(
			"*\n"
			".\n"
		),
		Area(".*\n"));
	
	assert_not_contains_both(
		Area(
			".*\n"
			"..\n"
		),
		Area("*\n"));
}

TEST(Area__Contains__SimpleCase)
{
	assert_not_contains_both(
		Area(
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...*.......\n"
			"...*.......\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_not_contains_both(
		Area(
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"..**.......\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_not_contains_both(
		Area(
			"........*..\n"
			"........*..\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_not_contains_both(
		Area(
			"...........\n"
			"........**.\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_contains(
		Area(
			"...........\n"
			"........*..\n"
			"...........\n"
			"....*......\n"
			"......*....\n"
			"...........\n"
			"....*......\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
}

TEST(Area__Contains__Inside)
{
	assert_not_contains_both(
		Area(
			"...........\n"
			"...........\n"
			"...........\n"
			".....**....\n"
			".....**....\n"
			"...........\n"
			"...........\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...**..**..\n"
			"...**..**..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_not_contains_both(
		Area(
			"...........\n"
			"...........\n"
			".....**....\n"
			"....****...\n"
			"....****...\n"
			".....**....\n"
			"...........\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...**..**..\n"
			"...**..**..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_contains(
		Area(
			"...........\n"
			"...........\n"
			".....**....\n"
			"....*..*...\n"
			"....*..*...\n"
			".....**....\n"
			"...........\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...**..**..\n"
			"...**..**..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
	
	assert_contains(
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...**..**..\n"
			"...**..**..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		),
		Area(
			"...........\n"
			"...******..\n"
			"...******..\n"
			"...**..**..\n"
			"...**..**..\n"
			"...******..\n"
			"...******..\n"
			"...........\n"
		));
}

TEST(Area__GetRect)
{
	ASSERT_IS(
		Rect2i({0, 0}, {0, 0}),
		(Area()).GetRect()
	);
	
	ASSERT_IS(
		Rect2i({0, 0}, {1, 1}),
		(Area("*\n")).GetRect()
	);
	
	ASSERT_IS(
		Rect2i({1, 1}, {1, 1}),
		(Area(".*\n..\n")).GetRect()
	);
	
	ASSERT_IS(
		Rect2i({4, 1}, {5, 6}),
		(Area(
			"...........\n"
			"........*..\n"
			"...........\n"
			"....*......\n"
			"......*....\n"
			"...........\n"
			"....*......\n"
			"...........\n"
		)).GetRect()
	);
}


#pragma clang diagnostic pop