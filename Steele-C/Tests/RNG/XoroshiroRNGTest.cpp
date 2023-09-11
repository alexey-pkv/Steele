#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include <set>
#include "../test_utils.h"


#include "RNG/XoroshiroRNG.h"


using namespace Steele;


bool try_assert_different(XoroshiroRNG& a, XoroshiroRNG& b)
{
	const int TEST_COUNT	= 10000;
	const int SCALE			= 10;
	
	int repeats = 0;
	
	for (int i = 0; i < TEST_COUNT; i++)
	{
		if (a.next_uint_64(0, SCALE) == b.next_uint_64(0, SCALE))
		{
			repeats++;
		}
	}
	
	auto actual_duplicates_prc = (double)repeats / (double)TEST_COUNT;
	auto maximum_duplicates_prc = 1.0 / (double)SCALE * 1.05;
	
	return actual_duplicates_prc < maximum_duplicates_prc;
}

bool try_assert_different(const std::string& sa, const std::string& sb)
{
	XoroshiroRNG a(sa);
	XoroshiroRNG b(sb);
	
	return try_assert_different(a, b);
}

void assert_different(const std::string& sa, const std::string& sb)
{
	ASSERT_TRUE(try_assert_different(sa, sb));
}

void assert_different(XoroshiroRNG& a, XoroshiroRNG& b)
{
	ASSERT_TRUE(try_assert_different(a, b));
}

void assert_same(XoroshiroRNG& a, XoroshiroRNG& b)
{
	const int TEST_COUNT	= 10000;
	
	for (int i = 0; i < TEST_COUNT; i++)
	{
		ASSERT_IS(a.next_uint_64(), b.next_uint_64());
	}
}

void assert_same(const std::string& str)
{
	XoroshiroRNG a(str);
	XoroshiroRNG b(str);
	
	assert_same(a, b);
}

void assert_range(int min, int max, int (*callback)(XoroshiroRNG&))
{
	XoroshiroRNG a(__FUNCTION__ );
	
	const int COUNT				= max - min + 1;
	const int TESTS_PER_ITEM	= 1000;
	const int TEST_COUNT		= TESTS_PER_ITEM * COUNT;
	
	const double COUNT_ERROR	= 0.1;
	const int MIN_COUNT			= (int)(TESTS_PER_ITEM * (1.0 - COUNT_ERROR));
	const int MAX_COUNT			= (int)(TESTS_PER_ITEM * (1.0 + COUNT_ERROR));
	
	std::map<int, int> found	= {};
	
	for (int i = 0; i < TEST_COUNT; i++)
	{
		auto val = callback(a);
		
		if (contains(found, val))
		{
			found[val]++;
		}
		else
		{
			found[val] = 1;
		}
		
		ASSERT_TRUE(val >= min);
		ASSERT_TRUE(val <= max);
	}
	
	ASSERT_IS(COUNT, found.size());
	double total_error = 0;
	
	for (auto &[_, count] : found)
	{
		total_error += ((double)std::abs(TESTS_PER_ITEM - count)) / (double)TESTS_PER_ITEM;
		
		ASSERT_TRUE(count >= MIN_COUNT);
		ASSERT_TRUE(count <= MAX_COUNT);
	}
	
	ASSERT_TRUE(total_error / (double)COUNT < 0.05);
}


TEST(XoroshiroRNG__Sanity)
{
	XoroshiroRNG rng;
	
	rng.reset_state("Hello World");
	rng.next_uint_64();
	
	rng.reset_state(rng.create_referenced_state(123));
	rng.next_uint_64();
}

TEST(XoroshiroRNG__TestRange)
{
	assert_range(0,		1,		[](auto p){ return (int)p.next_bool(); });
	assert_range(-10,	10,		[](auto p){ return (int)p.next_char(-10, 10); });
	assert_range(-1,	1,		[](auto p){ return (int)p.next_int_32(-1, 1); });
}

TEST(XoroshiroRNG__SameSeed__SameData)
{
	assert_same("");							// Empty
	assert_same("\n");							// Special characters
	assert_same("Hello World");					// Sanity word
	assert_same("1234567");						// 7 char
	assert_same("12345678");					// 8 char
	assert_same("123456789");					// 9 char
	assert_same(std::string(128, '0'));	// Long, exactly 8
	assert_same(std::string(201, '0'));	// Long, not rounded to 8
}

TEST(XoroshiroRNG__DifferentSeed__DiffernetData)
{
	// Make sure the assert function actually works
	ASSERT_FALSE(try_assert_different("A", "A"));
	
	
	// Sanity
	assert_different("Hello to you", "World");
	
	// With Empty
	assert_different("", "a");
	assert_different("", "1234567");
	assert_different("", "12345678");
	assert_different("", "123456789");
	assert_different("", "Hello World!!!!");
	
	// Same size
	assert_different("12345", "67890");
	assert_different("1", "2");
	
	// Similar seed
	assert_different("01234567890+", "01234567890-");
	assert_different("0001", "0010");
	assert_different("0001", "0000");
	assert_different("0000000", "0000001");
	assert_different("0000000", "1000000");
	assert_different("0000000_00000000_1", "00000000_00000000_2");
	assert_different("0000000_00000000_1", "00000000_00000001_0");
	
	// Longer/Shorter seed
	assert_different("Hello", "Hello World");
	assert_different("Hello World", "Hello World !!!");
	assert_different("1234567", "12345678");
	assert_different("123456789", "12345678");
	
	// Revers 
	assert_different("123456789",	"987654321");
	assert_different("12345678",	"87654321");
	assert_different("1234567",		"7654321");
}

TEST(XoroshiroRNG__StateResets)
{
	const int COUNT	= 100000;
	
	XoroshiroRNG rng("123");
	std::vector<uint64_t> v;
	
	v.reserve(COUNT);
	
	for (auto i = 0; i < COUNT; i++)
	{
		v.push_back(rng.next_uint_64());
	}
	
	
	rng.reset_state();
	
	
	for (auto i = 0; i < COUNT; i++)
	{
		auto curr = rng.next_uint_64();
		ASSERT_IS(v[i], curr);
	}
}


TEST(XoroshiroRNG__get_state__set_state)
{
	const int COUNT	= 100000;
	
	XoroshiroRNG rng(__FUNCTION__, COUNT);
	RandomState s = rng.get_state();
	
	std::vector<uint64_t> v;
	v.reserve(COUNT);
	
	for (auto i = 0; i < COUNT; i++)
	{
		v.push_back(rng.next_uint_64());
	}
	
	
	rng.set_state(s);
	
	
	for (auto i = 0; i < COUNT; i++)
	{
		auto curr = rng.next_uint_64();
		ASSERT_IS(v[i], curr);
	}
}


TEST(XoroshiroRNG__referenced_state_int__always_same_value)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(123));	rng.jump(100);
	XoroshiroRNG b(rng.create_referenced_state(123)); rng.jump(100);
	XoroshiroRNG c(rng.create_referenced_state(123)); rng.jump(100);
	
	assert_same(a, b);
	a.reset_state();
	assert_same(a, c);
}


TEST(XoroshiroRNG__referenced_state_float__always_same_value)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(123.0f));	rng.jump(100);
	XoroshiroRNG b(rng.create_referenced_state(123.0f)); rng.jump(100);
	XoroshiroRNG c(rng.create_referenced_state(123.0f)); rng.jump(100);
	
	assert_same(a, b);
	a.reset_state();
	assert_same(a, c);
}


TEST(XoroshiroRNG__referenced_state_vector2i__always_same_value)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state({ 1, 2 }));	rng.jump(100);
	XoroshiroRNG b(rng.create_referenced_state({ 1, 2 })); rng.jump(100);
	XoroshiroRNG c(rng.create_referenced_state({ 1, 2 })); rng.jump(100);
	
	assert_same(a, b);
	a.reset_state();
	assert_same(a, c);
}


TEST(XoroshiroRNG__referenced_state_vector3i__always_same_value)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state({ 1, 2, 3 })); rng.jump(100);
	XoroshiroRNG b(rng.create_referenced_state({ 1, 2, 3 })); rng.jump(100);
	XoroshiroRNG c(rng.create_referenced_state({ 1, 2, 3 })); rng.jump(100);
	
	assert_same(a, b);
	a.reset_state();
	assert_same(a, c);
}

TEST(XoroshiroRNG__referenced_state_vector2i__different_vectors)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state({ 1, 2 }));
	XoroshiroRNG b(rng.create_referenced_state({ 1, 1 }));
	XoroshiroRNG c(rng.create_referenced_state({ 2, 2 }));
	
	assert_different(a, b);
	assert_different(a, c);
	
	b.reset_state();
	c.reset_state();
	
	assert_different(b, c);
}

TEST(XoroshiroRNG__referenced_state_int__different_vectors)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(10));
	XoroshiroRNG b(rng.create_referenced_state(20));
	
	assert_different(a, b);
}

TEST(XoroshiroRNG__referenced_state_float__different_vectors)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(0.1f));
	XoroshiroRNG b(rng.create_referenced_state(0.2f));
	
	assert_different(a, b);
}

TEST(XoroshiroRNG__referenced_state_vector3i__different_vectors)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state({ 1, 2, 3 }));
	XoroshiroRNG b(rng.create_referenced_state({ 1, 1, 3 }));
	XoroshiroRNG c(rng.create_referenced_state({ 1, 2, 2 }));
	XoroshiroRNG d(rng.create_referenced_state({ 3, 2, 3 }));
	
	assert_different(a, b);
	assert_different(a, c);
	assert_different(a, d);
	
	b.reset_state();
	c.reset_state();
	d.reset_state();
	
	assert_different(b, c);
	assert_different(b, d);
	
	c.reset_state();
	d.reset_state();
	
	assert_different(c, d);
}


TEST(XoroshiroRNG__referenced_state__different_refereces__different_vectors)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(1));
	XoroshiroRNG b(rng.create_referenced_state(1.0f));
	XoroshiroRNG c(rng.create_referenced_state({1, 1}));
	XoroshiroRNG d(rng.create_referenced_state({1, 1, 1}));
	
	assert_different(a, b);
	assert_different(a, c);
	assert_different(a, d);
	
	b.reset_state();
	c.reset_state();
	d.reset_state();
	
	assert_different(b, c);
	assert_different(b, d);
	
	c.reset_state();
	d.reset_state();
	
	assert_different(c, d);
}


TEST(XoroshiroRNG__referenced_state__differnt_than_no_ref)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG a(rng.create_referenced_state(1));
	XoroshiroRNG b(rng.create_referenced_state(1.0f));
	XoroshiroRNG c(rng.create_referenced_state({1, 1}));
	XoroshiroRNG d(rng.create_referenced_state({1, 1, 1}));
	
	assert_different(rng, a);
	assert_different(rng, b);
	assert_different(rng, c);
	assert_different(rng, d);
}


TEST(XoroshiroRNG__referenced_state__from_another_referenced_state__resets)
{
	XoroshiroRNG rng;
	
	rng.reset_state(__FUNCTION__ );
	
	XoroshiroRNG cpy(rng.create_referenced_state(1));
	
	
	XoroshiroRNG from_copy_1(cpy.create_referenced_state(1.0f));
	XoroshiroRNG from_orig_1(rng.create_referenced_state(1.0f));
	assert_same(from_copy_1, from_orig_1);
	
	
	XoroshiroRNG from_copy_2(cpy.create_referenced_state(2));
	XoroshiroRNG from_orig_2(rng.create_referenced_state(2));
	assert_same(from_copy_2, from_orig_2);
	
	
	XoroshiroRNG from_copy_3(cpy.create_referenced_state({1, 1}));
	XoroshiroRNG from_orig_3(rng.create_referenced_state({1, 1}));
	assert_same(from_copy_3, from_orig_3);
	
	
	XoroshiroRNG from_copy_4(cpy.create_referenced_state({1, 1, 2}));
	XoroshiroRNG from_orig_4(rng.create_referenced_state({1, 1, 2}));
	assert_same(from_copy_4, from_orig_4);
}



#pragma clang diagnostic pop