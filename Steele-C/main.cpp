#include <iostream>
#include "DataTypes/Generation/DB/BrushDB.h"
#include "DataTypes/Generation/DB/PaletteDB.h"
#include "RNG/XoroshiroRNG.h"
#include "Generation/Brushes/GridBlock/GridBlockGenerator.h"


using namespace godot;
using namespace std;
using namespace Steele;


int main()
{
	GridBlockGenerator g;
	XoroshiroRNG rng;
	BlockGeneratorConfig cfg
	{
		.GridWidth			= 20,
		.GridHeight			= 20,
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
	
	rng.reset_state("My state");
	
	cout << g.generate(rng, cfg) << endl;
	
	cout << g.debug_map() << endl;
	
	return 0;
}

