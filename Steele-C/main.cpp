#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"


using namespace godot;
using namespace std;
using namespace Steele;


int main()
{
	vector<int> v;
	vector<int> w;
	
	v.reserve(120);
	
	std::swap(v, w);
	
	cout << v.capacity() << " " << w.capacity() << endl;
	
	return 0;
}

