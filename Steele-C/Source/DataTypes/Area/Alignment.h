#ifndef STEELE_ALIGNMENT_H
#define STEELE_ALIGNMENT_H


#include "DataTypes/Types.h"
#include "DataTypes/Area.h"

namespace Steele
{
	struct Alignment 
	{
	public:
		bool	IsSuccessful;
		v2i		Offset;
		
		
	public:
		~Alignment() = default;
		Alignment() = default;
		Alignment(const Alignment&) = default;
		Alignment(Alignment&&) = default;
		
		
	public:
		inline Area& Modify(Area& a) const { return a += Offset; }
		[[nodiscard]] inline Area Modify(const Area& a) const { return a + Offset; }
	};
}


#endif