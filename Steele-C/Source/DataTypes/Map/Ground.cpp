#include "Ground.h"
#include "Exceptions/JSONException.h"


using namespace Steele;


void GroundTile::json_write(const IDMap& map, nlohmann::json& into) const
{
	into = {
		{ "ID", map.require(ID) },
		{ "Direction", Dir }
	};
}

void GroundTile::json_read(const IDMap& map, const nlohmann::json& from)
{
	if (!from.contains("ID"))
		throw JSONException("Missing `ID` field for GroundTile JSON");
	if (!from.at("ID").is_string())
		throw JSONException("`ID` field must be string in GroundTile JSON");
	
	auto idPath = from.at("ID").get<std::string>();
	auto id = map.require(idPath);
	
	ID = id;
	Dir = from.at("Direction").get<Direction>();
}


void Ground::add(const GroundTile &gt)
{
	if (is_empty() || (remove(gt.ID) && is_empty()))
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

bool Ground::has(t_id id) const
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

bool Ground::remove(t_id id)
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
