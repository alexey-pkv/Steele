#include "test_utils.h"


#include "DataTypes/Types.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <algorithm>
#include <wildcards.hpp>
#include <wildcards_cx.hpp>


using namespace std;


std::map<string, size_t> name_length = {};
std::map<string, std::vector<test_function_t>> tests = {};


void sort_test_name_length(const test_function_t& test_data)
{
	auto& module_name	= test_data.module_name;
	auto& test_name		= test_data.test_name;
	
	auto length = test_name.length();
	auto existing = name_length.find(module_name);
	
	if (existing == name_length.end())
	{
		name_length[module_name] = length;
	}
	else
	{
		existing->second = max(existing->second, length);
	}
}

void sort_tests()
{
	for (auto& m : tests)
	{
		SORT_BY_FIELD_REF(m.second, const test_function_t&, index);
	}
}

void sort_test_order(const test_function_t& test_data)
{
	auto& module_name	= test_data.module_name;
	auto& test_name		= test_data.test_name;
	
	auto module = tests.find(module_name);
	
	if (module == tests.end())
	{
		tests[module_name] = { test_data };
	}
	else
	{
		module->second.push_back(test_data);
	}
}

void scan_tests()
{
	section_foreach_entry(tests_scope, test_function_provider, entry)
	{
		auto test_data = (*entry)();
		
		sort_test_name_length(test_data);
		sort_test_order(test_data);
	}
	
	sort_tests();
}

string generate_name_padding(const string& module_name, const string& test_name)
{
	auto max_length = name_length[module_name];
	auto test_name_length = test_name.length();
	auto res = string(max_length - test_name_length, ' ');
	
	return res;
}


#include <sstream>

void run_tests(const char* filter)
{
	string last_module;
	auto module_start = get_current_time();
	
	scan_tests();
	
	for (auto& m : tests)
	{
		auto& module_name	= m.first;
		
		if (last_module != module_name)
		{
			if (!last_module.empty())
			{
				cout << "] (" << fixed << get_runtime_ms(module_start) << ") ms" << endl;
			}
			
			last_module = "";
			module_start = get_current_time();
		}
		
		for (const auto& test_data : m.second)
		{
			auto& test_name		= test_data.test_name;
			auto& test		= test_data.test;
			
			if (filter != nullptr)
			{
				auto filter_pattern = string("*") + string (filter) + string("*");
				auto source = wildcards::cx::make_string_view(test_name.c_str(), test_name.length());
				auto pattern = wildcards::cx::make_string_view(filter_pattern.c_str(), filter_pattern.length());
	
				if (!wildcards::match(source, pattern).res)
				{
					continue;
				}
			}
			
			if (last_module.empty())
			{
				cout << module_name << endl << "[" << endl;
				last_module = module_name;
			}
			
			cout << "\t" << test_name;
			
			auto start_at = get_current_time();
			{
				test();
			}
			auto runtime = get_runtime_ms(start_at);
			
			auto res = generate_name_padding(module_name, test_name);
			
			cout 
				<< generate_name_padding(module_name, test_name)
				<< " (" << fixed << runtime << " ms)" << endl;
		}
	}
	
	if (!last_module.empty())
	{
		cout << "] (" << fixed << get_runtime_ms(module_start) << ") ms" << endl;
	}
}


double get_runtime_sec(std::chrono::system_clock::time_point tp)
{
	using std::chrono::duration;

	duration<double> sec_double = get_current_time() - tp;
	
	return sec_double.count();
}

double get_runtime_ms(std::chrono::system_clock::time_point tp)
{
	using std::chrono::duration;
	
	duration<double, std::milli> ms_double = get_current_time() - tp;
	
	return ms_double.count();
}

std::chrono::system_clock::time_point get_current_time()
{
	using std::chrono::high_resolution_clock;
	
	return high_resolution_clock::now();
}


std::string get_module_name(const char *source)
{
	string curr = __FILE__;
	
	auto name = string(source);
	auto last_index = curr.find_last_of('/');
	
	if (last_index == string::npos) last_index = curr.find_last_of('\\');
	if (last_index == string::npos) return source;
	
	name = name.substr(last_index + 1);
	
	last_index = name.find_last_of('.');
	
	if (last_index != string::npos)
	{
		name = name.substr(0, last_index);
	}
	
	return name;
}

std::string get_test_name(const char *source)
{
	return source;
}
