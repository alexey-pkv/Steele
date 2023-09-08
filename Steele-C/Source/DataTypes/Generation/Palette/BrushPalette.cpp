#include "BrushPalette.h"

#include <utility>


sptr<Steele::IBrush> Steele::BrushPalette::get(t_id id)
{
	auto kvp = m_brushes.find(id);
	return kvp == m_brushes.end() ? nullptr : kvp->second;
}

sptr<const Steele::IBrush> Steele::BrushPalette::get(t_id id) const
{
	auto kvp = m_brushes.find(id);
	return kvp == m_brushes.end() ? nullptr : kvp->second;
}

void Steele::BrushPalette::add(t_id id, sptr<Steele::IBrush> brush)
{
	m_brushes[id] = std::move(brush);
}
