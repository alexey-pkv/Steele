#include "FillBrush.h"

#include "Base/Generation/IGenerationScope.h"
#include "DataTypes/Generation/GenerationResourcesDB.h"
#include "Exceptions/JSONException.h"


void Steele::FillBrush::paint(Steele::IGenerationScope& scope, const Steele::Area& area) const
{
	if (m_groundID == STEELE_NULL_ID && m_paletteID == STEELE_NULL_ID)
		throw MisconfiguredBrushException("One of Ground ID or Palette ID must be set for a Fill Brush");
	if (area.is_empty())
		return;
	
	Direction	dir;
	Cell*		cell;
	t_id		groundID = m_groundID;
	
	const Palette*	palette = nullptr;
	
	auto& map = scope.map();
	auto& rng = scope.rng();
	
	if (groundID == STEELE_NULL_ID)
	{
		palette = scope.db().palettes().get(m_paletteID);
		
		if (palette == nullptr)
		{
			throw NoPaletteException();
		}
		else if (palette->ground().is_empty())
		{
			throw NoGroundInPaletteException();
		}
	}
	
	for (auto v : area)
	{
		dir = m_dir.get(rng);
		cell = map.get(v);
		
		if (palette)
		{
			groundID = palette->ground().select_random(rng);
		}
		
		cell->Ground.set(groundID, dir, 0);
	}
}

bool Steele::FillBrush::can_fill(const Steele::Area& a) const
{
	return true;
}


void Steele::FillBrush::json_write(nlohmann::json& into) const
{
	auto& map = IDMap::global();
	
	into = nlohmann::json::object();
	
	m_dir.json_write(into["dir"]);
	
	if (m_paletteID != STEELE_NULL_ID)
	{
		into["palette"]	= map.require(m_paletteID);
	}
	else if (m_groundID != STEELE_NULL_ID)
	{
		into["ground"]	= map.require(m_groundID);
	}
}

void Steele::FillBrush::json_read(const nlohmann::json& from)
{
	auto& map = IDMap::global();
	
	m_groundID = STEELE_NULL_ID;
	m_paletteID = STEELE_NULL_ID;
	
	m_dir.json_read(from);
	
	if (from.contains("palette"))
	{
		m_paletteID = map.require(from["palette"].get<string>());
	}
	else if (from.contains("ground"))
	{
		m_groundID = map.require(from["ground"].get<string>());
	}
	else
	{
		throw JSONException("Either ground or palette must be set!");
	}
}
