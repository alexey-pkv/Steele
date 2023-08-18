#include "CellConditions.h"


static const Steele::CellConditions DEFAULT = {};


bool Steele::CellConditions::IsConsistent(const Steele::CellConditions &conditions) const
{
	if (conditions.m_roadCondition == m_roadCondition ||
		conditions.m_roadCondition == None || 
		m_roadCondition == None)
	{
		return true;
	}
	
	return false;
}

bool Steele::CellConditions::MergeFrom(const Steele::CellConditions &conditions)
{
	if (!IsConsistent(conditions))
		return false;
	
	if (conditions.m_roadCondition != None)
	{
		m_roadCondition = conditions.m_roadCondition;
	}
	
	return true;
}

bool Steele::CellConditions::IsConsistent(const Steele::Cell &cell) const
{
	if (m_roadCondition == RequireNoRoad)
	{
		if (cell.IsRoad)
		{
			return false;
		}
	}
	else if (m_roadCondition == RequireRoad)
	{
		if (!cell.IsRoad)
		{
			return false;
		}
	}
	
	return true;
}
