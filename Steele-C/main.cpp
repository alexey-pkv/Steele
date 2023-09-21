#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Brushes/GridBlock/GridBlockGenerator.h"
#include "Generation/Brushes/VoronoiSquare/VoronoiSquareGenerator.h"


using namespace godot;
using namespace std;
using namespace Steele;


int main()
{
	for (int i = 0; i < 100; i++)
	{
		std::string s { (char)i };
		
		XoroshiroRNG rng(s);
		VoronoiSquareGenerator gen;
		
		int border	= 10;
		int size	= 50;
		int count	= 100;
		
		gen.generate(rng, { size, size }, count);
		
		for (auto& n : gen.areas())
		{
			if (n.Sign != '\0') continue;
			
			auto& a = n.TotalArea;
			
			if (a.left() < border || a.right() >= size - border || 
				a.bottom() < border || a.top() >= size - border)
			{
				n.Sign = 'O';
			}
			else
			{
				n.Sign = ' ';
			}
		}
		
		cout << gen.debug_info() << endl;
	}
	
	return 0;
}

