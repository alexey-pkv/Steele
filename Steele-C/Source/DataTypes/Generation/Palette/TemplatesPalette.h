#ifndef STEELE_TEMPLATESPALETTE_H
#define STEELE_TEMPLATESPALETTE_H


#include <unordered_map>

#include "DataTypes/Area.h"
#include "Generation/Brushes/TemplateBrush.h"
#include "IPalette.h"


namespace Steele
{
	/*
	class TemplatesPalette : public IPalette
	{
	private:
		std::string m_name;
		std::unordered_map<Area, std::map<std::string, TemplateBrush*>> m_templatesByArea;
		std::map<std::string, TemplateBrush> m_templatesByName;
		
		
	private:
		void AddToByAreaMap(Steele::TemplateBrush& local);
		
		
	public:
		TemplatesPalette() = default;
		~TemplatesPalette() = default;
		
		
	public:
		const std::string& Name() const override;
		
		
	public:
		inline void SetName(const std::string& name) { m_name = name; }
		
		
	public:
		void add(const TemplateBrush& brush);
		void add(TemplateBrush&& brush);
		void Remove(const std::string& name);
		
		bool has(const std::string& name) const;
		bool HasAny(const Area& area) const;
		const TemplateBrush* Get(const std::string& name) const;
		
		const TemplateBrush* GetRandom(RNG::IRNG& rng, const Area& area) const;
	};
	 */
}


#endif