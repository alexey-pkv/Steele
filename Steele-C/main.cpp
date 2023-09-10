#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"


using namespace godot;
using namespace std;
using namespace Steele;


int main()
{
	Steele::RNG::XoroshiroRNG x("Asd");
	
	BrushDB a;
	
	cout << x.next<int>() << endl;
	
	return 0;
}

