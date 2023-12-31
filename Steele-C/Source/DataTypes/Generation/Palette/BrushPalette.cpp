#include "BrushPalette.h"


#include "Base/Generation/IGenerationScope.h"
#include "DataTypes/Generation/GenerationResourcesDB.h"


using namespace Steele;


const IBrush* BrushPalette::select_random(const map<t_id, float>& from, IGenerationScope& scope, const Area* a) 
{
	GenericIDPalette curr;
	const auto& db = scope.db().brushes();
	
	for (auto [id, w] : from)
	{
		auto brush = db.require(id);
		
		if (a && !brush->can_fill(*a))
			continue;
		
		curr.add(id, w);
	}
	
	if (curr.is_empty())
		throw PaintException("No brushes found to fill area");
	
	auto id = curr.select_random(scope.rng());
	
	return db.require(id);
}

const IBrush* BrushPalette::select_random(IGenerationScope& scope) const
{
	return select_random(palette(), scope, nullptr);
}

const IBrush* BrushPalette::select_random(IGenerationScope& scope, const Area& a) const
{
	return select_random(palette(), scope, &a);
}

const IBrush* BrushPalette::select_random_where(IGenerationScope& scope, const Area& a, function<bool(const IBrush*)>& lambda) const
{
	std::map<t_id, float> map;
	
	const auto& db = scope.db().brushes();
	
	for (auto t : palette())
	{
		auto brush = db.get(t.first);
		
		if (!brush)
			continue;
		
		if (lambda(brush))
		{
			map[t.first] = t.second;
		}
	}
	
	return select_random(palette(), scope, &a);
}

void BrushPalette::get_reduced_palette(BrushPalette& p, IGenerationScope& scope, std::function<bool(
		const IBrush*)>& where) const
{
	const auto& db = scope.db().brushes();
	
	for (auto t : palette())
	{
		auto brush = db.get(t.first);
		
		if (!brush)
			continue;
		
		if (where(brush))
		{
			p.add(t.first, t.second);
		}
	}
}

void BrushPalette::reduce_palette(IGenerationScope& scope, function<bool(const IBrush*)>& where)
{
	const auto& db = scope.db().brushes();
	auto& p = palette();
	
	for (auto it = p.cbegin(); it != p.cend();)
	{ 
		auto brush = db.require(it->first);
		
		if (!where(brush))
		{
			it = p.erase(it);
		}
		else
		{
			it++;
		}
	}
}
