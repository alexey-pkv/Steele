#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Brushes/GridBlock/GridBlockGenerator.h"
#include "Generation/Brushes/VoronoiSquare/VoronoiSquareGenerator.h"
#include "Debug/MapDebug.h"


using namespace godot;
using namespace std;
using namespace Steele;


void foo()
{
	vector<int> v;
	vector<int> w;
	GridBlockGenerator g;
	XoroshiroRNG rng;
	BlockGeneratorConfig cfg
	{
		.GridWidth			= 10,
		.GridHeight			= 10,
		.SingleBlockSize	= 20,
		.RoadWidth			= 5,
		.Blocks =
		{
			BlockTypeConfig {
				.Size	= v2i_one,
				.Min	= 0,
				.Max	= -1,
				.Weight	= 1
			},
			BlockTypeConfig {
				.Size	= { 1, 2 },
				.Min	= 1,
				.Max	= -1,
				.Weight	= 50
			},
			BlockTypeConfig {
				.Size	= { 2, 1 },
				.Min	= 1,
				.Max	= -1,
				.Weight	= 50
			},
			BlockTypeConfig {
				.Size	= { 2, 2 },
				.Min	= 1,
				.Max	= -1,
				.Weight	= 50
			},
			BlockTypeConfig {
				.Size	= { 3, 2 },
				.Min	= 0,
				.Max	= -1,
				.Weight	= 25
			},
			BlockTypeConfig {
				.Size	= { 2, 3 },
				.Min	= 0,
				.Max	= -1,
				.Weight	= 25
			},
			BlockTypeConfig {
				.Size	= { 3, 3 },
				.Min	= 1,
				.Max	= 2,
				.Weight	= 15
			}
		}
	};
	
	v.reserve(120);
	rng.reset_state("My state");
	
	std::swap(v, w);
	cout << g.generate(rng, cfg) << endl;
	
	cout << v.capacity() << " " << w.capacity() << endl;
	cout << g.debug_map() << endl;
}

void foo_2(std::string s)
{
	XoroshiroRNG rng(s);
	VoronoiSquareGenerator gen;
	
	int border	= 2;
	int size	= 20;
	int count	= 50;
	
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


int main()
{
	auto a = Area(
		"***\n"
		"***\n"
	);
	
	auto brush = CanvasBrush::debug_create(a, 1);
	auto& c = brush.canvas();
	auto info = debug_info(c);
	
	cout << info << endl;
	
	return 0;
}

