#ifndef STEELE_CELLCONDITIONS_H
#define STEELE_CELLCONDITIONS_H


#include "Map/Cell.h"

namespace Steele
{
	class CellConditions
	{
	public:
		enum RoadCondition : char
		{
			None			= 0,
			RequireRoad		= 1,
			RequireNoRoad	= 2
		};
		
		
	private:
		RoadCondition m_roadCondition = None;
		
		
	public:
		inline RoadCondition GetRoadCondition() const { return m_roadCondition; }
		inline void SetRoadCondition(RoadCondition condition) { m_roadCondition = condition; }
		inline bool IsConsistent(const CellConditions* conditions) const { return IsConsistent(*conditions); } 
		inline bool MergeFrom(const CellConditions* conditions) { return MergeFrom(*conditions); }
		
	public:
		bool IsConsistent(const CellConditions& conditions) const;
		bool MergeFrom(const CellConditions& conditions);
		
		bool IsConsistent(const Cell& cell) const;
		
		
	public:
		static const CellConditions DEFAULT;
	};
}


#endif