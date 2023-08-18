#include <iostream>
#include <wildcards.hpp>


#include "test_utils.h"


using namespace std;


int main(int c, char** arg)
{
	// Force cout to flush after each input. This will help in debugging.
	std::cout << std::unitbuf; 
	
	const char* filter = c > 1 ?arg[1] : nullptr;
	
	cout 
		<< endl << "-----------------------" << endl 
		<< "Running Tests..." 
		<< endl << "-----------------------" << endl << endl;
	
	auto start_at = get_current_time();
	{
		run_tests(filter);
	}
	auto runtime = get_runtime_sec(start_at);
	
	cout 
		<< endl << "-----------------------" << endl 
		<< "Complete in " << fixed << runtime << " seconds" << endl;
}