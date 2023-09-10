#include <chrono>
#include <cstring>
#include <string>
#include <cassert>


#define ASSERT(exp) assert(exp)
#define ASSERT_NOT(exp) ASSERT(!(exp))
#define ASSERT_IS(exp, val) ASSERT((exp) == (val))
#define ASSERT_FALSE(exp) ASSERT((exp) == false)
#define ASSERT_FAIL() ASSERT(false)
#define ASSERT_TRUE(exp) ASSERT((exp) == true)
#define ASSERT_NOT_NULL(exp) ASSERT((exp) != nullptr)
#define ASSERT_NULL(exp) ASSERT((exp) == nullptr)
#define ASSERT_IS_NOT(exp, val) ASSERT(exp != val)


typedef void (*test_function)();

typedef struct
{
	test_function	test;
	std::string		module_name;
	std::string		test_name;	
	int 			index;
}
test_function_t;

typedef test_function_t (*test_function_provider)();

typedef struct
{
	test_function_provider test_definition;
}
test_function_provider_t;


std::string get_module_name(const char* source);
std::string get_test_name(const char* source);



#define TEST(func_test)											\
	void func_test();											\
	test_function_t func_test##_function_definition()			\
	{															\
		return													\
		{														\
			.test			= func_test,						\
			.module_name	= get_module_name(__FILE__),		\
			.test_name		= get_test_name(#func_test),		\
			.index			= __COUNTER__						\
		};														\
	};															\
	static test_function_provider_t ptr_##func_test				\
	__attribute((used, section("tests_scope"))) = {				\
		.test_definition = func_test##_function_definition,		\
	};															\
	void func_test()


#define section_foreach_entry(section_name, type_t, elem)	\
	 for (type_t *elem =									\
		({													\
			extern type_t __start_##section_name;			\
			&__start_##section_name;						\
		});													\
		elem !=												\
		({													\
			extern type_t __stop_##section_name;			\
			&__stop_##section_name;							\
		});													\
		++elem)


double get_runtime_sec(std::chrono::system_clock::time_point tp);
double get_runtime_ms(std::chrono::system_clock::time_point tp);


std::chrono::system_clock::time_point get_current_time();


void run_tests(const char* filter);