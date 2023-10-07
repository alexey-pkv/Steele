#include "Ground.h"
#include "Exceptions/JSONException.h"

#include "json.h"


using namespace Steele;


void GroundTile::json_write(nlohmann::json& into) const
{
	into = {
		{ "id", IDMap::global().require(ID) },
		{ "dir", Dir }
	};
}

void GroundTile::json_read(const nlohmann::json& from)
{
	if (!from.contains("id"))
		throw JSONException("Missing `id` field for GroundTile JSON");
	if (!from.at("id").is_string())
		throw JSONException("`id` field must be string in GroundTile JSON");
	
	auto idPath = from.at("id").get<std::string>();
	auto id = IDMap::global().require(idPath);
	
	ID = id;
	Dir = from.at("dir").get<Direction>();
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

void Ground::json_write(nlohmann::json& into) const
{
	auto orderedGround = m_ground;
	std::sort(orderedGround.begin(), orderedGround.end(), GroundTile::sort_by_index);
	
	into = orderedGround;
}

void Ground::json_read(const nlohmann::json& from)
{
	if (!from.is_array())
		throw JSONException("Expected array. Got some fucking dumb shit instead");
	
	m_ground = from;
	
	int index = 0;
	
	for (auto& item : m_ground)
	{
		item.Index = index++;
	}
}
