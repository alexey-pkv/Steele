#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Brushes/GridBlock/GridBlockGenerator.h"
#include "Generation/Brushes/VoronoiSquare/VoronoiSquareGenerator.h"
#include "Debug/MapDebug.h"
#include "Generation/GenerationScope.h"
#include "Generation/Brushes/RowBrush.h"


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
	GenerationScope scope;
	
	scope.set_in_debug_mode();
	
	auto& brushDB = scope.brush_db();
	auto p = scope.palette_db().create(100);
	
	brushDB.create_canvas(2)->debug_set(Area("**\n" "**\n"), 2);
	brushDB.create_canvas(3)->debug_set(Area("***\n" "***\n" "***\n"), 3);
	brushDB.create_canvas(4)->debug_set(Area("****\n" "****\n" "****\n" "****\n"), 4);
	brushDB.create_canvas(32)->debug_set(Area("**\n" "**\n" "**\n"), 32);
	brushDB.create_canvas(23)->debug_set(Area("***\n" "***\n"), 23);
	
	p->brushes().add(2, 1);
	p->brushes().add(3, 1);
	p->brushes().add(4, 1);
	p->brushes().add(32, 1);
	p->brushes().add(23, 1);
	
	scope.rng_state().reset_state("Hello World");
	
	RowBrush rb;
	
	rb.set_palette_id(p->get_id());
	rb.set_min_height(1);
	rb.set_max_height(3);
	
	Area target(0, 0, 23, 10);
	
	rb.paint(scope, target);
	
	cout << scope.map().debug_info() << endl;
	
	return 0;
}

