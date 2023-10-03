#include <iostream>
#include <chrono>
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


std::chrono::system_clock::time_point get_current_time()
{
	using std::chrono::high_resolution_clock;
	
	return high_resolution_clock::now();
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

void foo_3()
{
	GenerationScope scope;
	
	// scope.set_in_debug_mode();
	
	auto& brushDB = scope.brush_db();
	auto p = scope.palette_db().create(100);
	
	auto f = brushDB.create_fill(1);
	f->set_ground_id(1);
	
	brushDB.create_canvas(2)->debug_set(Area("**\n" "**\n"), 2);
	brushDB.create_canvas(3)->debug_set(Area("***\n" "***\n" "***\n"), 3);
	brushDB.create_canvas(4)->debug_set(Area("****\n" "****\n" "****\n" "****\n"), 4);
	brushDB.create_canvas(32)->debug_set(Area("**\n" "**\n" "**\n"), 32);
	brushDB.create_canvas(23)->debug_set(Area("***\n" "***\n"), 23);
	brushDB.create_canvas(52)->debug_set(Area("**\n" "**\n" "**\n" "**\n" "**\n"), 32);
	brushDB.create_canvas(25)->debug_set(Area("*****\n" "*****\n"), 23);
	
	p->brushes().add(2, 1);
	p->brushes().add(3, 1);
	p->brushes().add(4, 1);
	p->brushes().add(32, 1);
	p->brushes().add(23, 1);
	p->brushes().add(52, 1);
	p->brushes().add(25, 1);
	
	scope.rng_state().reset_state("Hello World 2");
	
	RowBrush rb;
	
	rb.set_fill_id(1);
	rb.set_palette_id(p->get_id());
	rb.set_min_height(3);
	rb.set_max_height(4);
	
	Area target(0, 0, 27, 12);
	
	auto start_at = get_current_time();
	{
		rb.paint(scope, target);
	}
	auto runtime = get_runtime_sec(start_at);
	
	cout << "-----------------------" << endl;
	cout << scope.map().debug_info() << endl;
	cout << "-----------------------" << endl 
		<< "Complete in " << fixed << runtime << " seconds" << endl;
}


#include "Library/json.hpp"
#include "Base/IJsonable.h"


using namespace nlohmann;


int main()
{
	json j;
	
	
	DirectionSettings ds;
	
	ds.VariableDirection[2] = 0.5;
	ds.SettingType = Steele::DirectionSettings::Type::Constant;
	ds.json_write(j);
	
	cout << j.dump(1, '\t') << endl;
	
	
	
	return 0;
}

