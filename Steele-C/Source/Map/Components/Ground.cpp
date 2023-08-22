#include "Ground.h"


using namespace Steele;


void Ground::Add(const GroundTile &gt)
{
	if (IsEmpty() || (Remove(gt.ID) && IsEmpty()))
	{
		m_ground.push_back(gt);
		return;
	}
	
	if (m_ground.begin()->Index > gt.Index)
	{
		m_ground.insert(std::begin(m_ground), gt);
		return;
	}
	
	for (auto n = m_ground.begin() + 1; n < m_ground.end(); n++)
	{
		if (n->Index > gt.Index)
		{
			m_ground.insert(n - 1, gt);
			return;
		}
	}
	
	m_ground.push_back(gt);
}

bool Ground::Has(t_id id) const
{
	for (const auto& a : m_ground)
	{
		if (a.ID == id)
		{
			return true;
		}
	}
	
	return false;
}

bool Ground::Remove(t_id id)
{
	for (auto n = m_ground.begin(); n < m_ground.end(); n++)
	{
		if (n->ID == id)
		{
			m_ground.erase(n);
			return true;
		}
	}
	
	return false;
}
