#include <iostream>
#include "godot_cpp/variant/rect2i.hpp"
#include "DataTypes/Area.h"
#include "DataTypes/Area/Alignment.h"
#include "Utils.h"
#include "DataTypes/Area/outline_scalar_iterator.h"
#include "DataTypes/Area/AlignSettings.h"
#include "Exceptions/SteeleException.h"
#include "Base/Map/TransformedMap.h"
#include "Base/Map/SimpleMap.h"
#include "Base/Map/StackedMap.h"
#include "DataTypes/Map/Cell.h"
#include "Generation/Map/TransformationStack.h"
#include "RNG/XoroshiroRNG.h"

#include <chrono>
#include <set>


using namespace godot;
using namespace std;
using namespace Steele;


class GenMap
{
private:
	SimpleMap<Cell> m_map = {};
	TransformedMap<Cell> m_transformed;
	StackedMap<Cell> m_stacked;
	TransformationStack m_transformations;
	
public:
	GenMap() :
		m_transformed(m_map),
		m_stacked(m_transformed)
	{
		
	}
};


int main()
{
	
	cout << typeid(NotImplementedException).name() <<endl;
	Steele::RNG::XoroshiroRNG rng("hello");
	
	rng.SetState({1, 2});
	
	cout << rng.Next<char>(1, 2) << endl;
	
	return 0;
}

