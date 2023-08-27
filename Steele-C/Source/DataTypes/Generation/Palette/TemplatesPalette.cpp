#include "TemplatesPalette.h"

/*
const std::string &Steele::TemplatesPalette::Name() const
{
	return m_name;
}


void Steele::TemplatesPalette::AddToByAreaMap(Steele::TemplateBrush& local)
{
	auto& refArea = local.Area;
	
	if (m_templatesByArea.find(refArea) == m_templatesByArea.end())
		m_templatesByArea[refArea] = {};
	
	m_templatesByArea[refArea][local.Name] = &local;
}


void Steele::TemplatesPalette::add(const Steele::TemplateBrush &brush)
{
	auto name = brush.Name;
	
	Remove(name);
	
	m_templatesByName.emplace(name, brush);
	
	AddToByAreaMap(m_templatesByName[name]);
}

void Steele::TemplatesPalette::add(Steele::TemplateBrush &&brush)
{
	auto name = brush.Name;
	
	Remove(name);
	
	m_templatesByName.emplace(std::move(brush.Name), std::move(brush));
	
	AddToByAreaMap(m_templatesByName[name]);
}

void Steele::TemplatesPalette::Remove(const string &name)
{
	if (m_templatesByName.find(name) == m_templatesByName.end())
		return;
	
	auto& area = m_templatesByName[name].Area;
	auto& byArea = m_templatesByArea[area];
	
	m_templatesByName.erase(name);
	byArea.erase(name);
	
	if (byArea.empty())
	{
		m_templatesByArea.erase(area);
	}
}

bool Steele::TemplatesPalette::has(const string &name) const
{
	return m_templatesByName.find(name) != m_templatesByName.end();
}

bool Steele::TemplatesPalette::HasAny(const Steele::Area &area) const
{
	return m_templatesByArea.find(area) != m_templatesByArea.end();
}

const Steele::TemplateBrush* Steele::TemplatesPalette::Get(const string &name) const
{
	return m_templatesByName.find(name) == m_templatesByName.end() ? nullptr : &m_templatesByName.at(name);
}

const Steele::TemplateBrush* Steele::TemplatesPalette::GetRandom(Steele::RNG::IRNG &rng, const Steele::Area &area) const
{
	auto it = m_templatesByArea.find(area);
	
	if (it == m_templatesByArea.end())
		return nullptr;
	
	auto& map = it->second;
	
	auto index = rng.NextInt(0, (int)map.size() - 1);
	auto curr = map.begin();
	
	while (index-- > 0)
	{
		curr++;
	}
	
	return curr->second;
}

*/