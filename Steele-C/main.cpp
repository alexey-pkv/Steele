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

#include <chrono>
#include <set>


using namespace godot;
using namespace std;
using namespace Steele;




int main()
{
	SimpleMap<int> map1;
	StackedMap<int> map(map1);
	
	
	return 0;
}

