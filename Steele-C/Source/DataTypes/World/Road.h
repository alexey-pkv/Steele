#ifndef STEELE_ROAD_H
#define STEELE_ROAD_H


#include "DataTypes/Types.h"
#include "Element.h"


namespace Steele
{
	struct Road : public Element
	{
	public:
		std::string Name;
		v2i 		StartAt;
		v2i 		EndAt;
		t_id		ParentLocationID;
		int 		Width;
		int			Length;
		int 		SegmentLength;
	};
}


#endif