#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-assert-side-effect"


#include "test_utils.h"
#include "Base/Map/SimpleMap.h"


using namespace Steele;


class TestCell
{
public:
	int arg1;
	int arg2;
	int json_arg1;
	int json_arg2;
	int val;
	
	
public: 
	inline void json_write(nlohmann::json& into, int a1, int a2) const
	{
		into["val"] = val;
		into["arg1"] = a1;
		into["arg2"] = a2;
	}
	
	template<class ... ARG>
	inline void json_read(const nlohmann::json& from, int a1, int a2)
	{
		arg1 = a1;
		arg2 = a2;
		
		val = from["val"].get<int>();
		json_arg1 = from["arg1"].get<int>();
		json_arg2 = from["arg2"].get<int>();
	}
};


TEST(SimpleMap__JSON__Read__Container_Reset)
{
	nlohmann::json json;
	SimpleMap<TestCell> original;
	SimpleMap<TestCell> result;
	
	result.get({0, 0, 0});
	
	
	original.json_write(json, 1, 2);
	result.json_read(json, 1, 2);
	
	
	ASSERT_IS(0, result.size());
}


TEST(SimpleMap__JSON__Sanity)
{
	nlohmann::json json;
	SimpleMap<TestCell> original;
	SimpleMap<TestCell> result;
	
	
	auto a = original.get({0, 0, 0});
	auto b = original.get({1, 2, 3});
	
	a->val = 1;
	b->val = 123;
	
	
	original.json_write(json, 1, 2);
	cout << json.dump(1, '\t') << endl;
	result.json_read(json, 3, 4);
	
	
	ASSERT_IS(2, result.size());
	
	ASSERT_IS(1, result.get({0, 0, 0})->val);
	ASSERT_IS(1, result.get({0, 0, 0})->json_arg1);
	ASSERT_IS(2, result.get({0, 0, 0})->json_arg2);
	ASSERT_IS(3, result.get({0, 0, 0})->arg1);
	ASSERT_IS(4, result.get({0, 0, 0})->arg2);
	
	ASSERT_IS(123,	result.get({1, 2, 3})->val);
	ASSERT_IS(1,	result.get({1, 2, 3})->json_arg1);
	ASSERT_IS(2,	result.get({1, 2, 3})->json_arg2);
	ASSERT_IS(3,	result.get({1, 2, 3})->arg1);
	ASSERT_IS(4,	result.get({1, 2, 3})->arg2);
}


#pragma clang diagnostic pop
