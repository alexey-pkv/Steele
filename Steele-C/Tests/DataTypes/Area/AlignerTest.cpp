#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "test_utils.h"
#include "DataTypes/Area.h"
#include "DataTypes/Area/Aligner.h"


using namespace Steele;


typedef Alignment (*align_func)(const Area& source, const Area& target);
void assert_alignment(Area& source, const Area& target, align_func f, const string& exp)
{
	Area at = Area(target);
	Area aexp = Area(exp);
	
	
	auto a = f(source, at);
	
	
	ASSERT_TRUE(a.IsSuccessful);
	
	
	at += a.Offset;
	at ^= source;
	
	
	if (at != aexp)
	{
		cout << endl;
		cout << "Expected xor result to be: " << endl << aexp.debug_info() << endl;
		cout << "Got result: " << endl << at.debug_info() << endl;
		ASSERT(false);
	}
}


TEST(Aligner__Inside__SimpleCase)
{
	Area a = Area(
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*******.\n"  // 5
		".*******.\n"  // 4
		".*******.\n"  // 3
		".*******.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	Area b = Area(
		"..**\n"
		"..**\n"
		"....\n"
		"....\n"
		"....\n"
	);
	
	
	assert_alignment(a, b, Aligner::InsideTopRight,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*****...\n"  // 5
		".*****...\n"  // 4
		".*******.\n"  // 3
		".*******.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideTopLeft,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		"...*****.\n"  // 5
		"...*****.\n"  // 4
		".*******.\n"  // 3
		".*******.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideBottomRight,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*******.\n"  // 5
		".*******.\n"  // 4
		".*****...\n"  // 3
		".*****...\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideBottomLeft,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*******.\n"  // 5
		".*******.\n"  // 4
		"...*****.\n"  // 3
		"...*****.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideLeftBottom,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*******.\n"  // 5
		".*******.\n"  // 4
		".*******.\n"  // 3
		".*..****.\n"  // 2
		"....***..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideLeftTop,
		
	//   012345678
		".........\n"  // 7
		"....***..\n"  // 6
		".*..****.\n"  // 5
		".*******.\n"  // 4
		".*******.\n"  // 3
		".*******.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideRightBottom,
		
	//   012345678
		".........\n"  // 7
		"..*****..\n"  // 6
		".*******.\n"  // 5
		".*******.\n"  // 4
		".*******.\n"  // 3
		".****..*.\n"  // 2
		"..***....\n"  // 1
		".........\n"  // 0
	);
	
	assert_alignment(a, b, Aligner::InsideRightTop,
		
	//   012345678
		".........\n"  // 7
		"..***....\n"  // 6
		".****..*.\n"  // 5
		".*******.\n"  // 4
		".*******.\n"  // 3
		".*******.\n"  // 2
		"..*****..\n"  // 1
		".........\n"  // 0
	);
}


TEST(Aligner__Adjacent__SimpleCase)
{
	Area a = Area(
	//   012345678901
		"............\n"  // 9
		"....*.....*.\n"  // 8
		".....*****..\n"  // 7
		".....*****..\n"  // 6
		".....*****..\n"  // 5
		".....*****..\n"  // 4
		"....*.....*.\n"  // 3
		"............\n"  // 2
		"............\n"  // 1
		"............\n"  // 0
	);
	
	Area b = Area(
		"..**\n"
		"..**\n"
		"....\n"
		"....\n"
		"....\n"
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentRightBottom,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.**..\n"  // 4
		"....*.....***..\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentRightTop,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"....*.....***..\n"  // 8
		".....*****.**..\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentLeftBottom,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		"..**.*****.....\n"  // 4
		"..***.....*....\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentLeftTop,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"..***.....*....\n"  // 8
		"..**.*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentTopLeft,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"....**.........\n"  // 10
		"....**.........\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentTopRight,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		".........**....\n"  // 10
		".........**....\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		"...............\n"  // 2
		"...............\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentBottomLeft,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		"....**.........\n"  // 2
		"....**.........\n"  // 1
		"...............\n"  // 0
	);
	
	
	assert_alignment(a, b, Aligner::AdjacentBottomRight,
	//   012345678901
		"...............\n"  // 12
		"...............\n"  // 11
		"...............\n"  // 10
		"...............\n"  // 9
		"....*.....*....\n"  // 8
		".....*****.....\n"  // 7
		".....*****.....\n"  // 6
		".....*****.....\n"  // 5
		".....*****.....\n"  // 4
		"....*.....*....\n"  // 3
		".........**....\n"  // 2
		".........**....\n"  // 1
		"...............\n"  // 0
	);
}

#pragma clang diagnostic pop
