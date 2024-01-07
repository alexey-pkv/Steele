#include "Region.h"


using namespace Steele;


Region::Region(v3i index, v3i size)
{
	set_dimensions(index, size);
}


void Region::set_dimensions(v3i index, v3i size)
{
	Index = index;
	Offset = { index.x * size.x, index.y * size.y, index.z * size.z };
}

