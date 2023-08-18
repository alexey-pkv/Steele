#include "Aligner.h"


Steele::Aligner::Aligner(const Steele::Area& source, const Steele::Area &target): 
	m_target(target),
	m_source(source)
{
	
}

int Steele::Aligner::GetDist(outline_scalar_iterator &source, outline_scalar_iterator &target)
{
	return 0;
}

bool Steele::Aligner::Align(AlignSettings &settings, Steele::Alignment &result)
{
	result.IsSuccessful = false;
	
	auto source = settings.SourceIterator.begin();
	auto target = settings.TargetIterator.begin();
	auto sourceEnd = settings.SourceIterator.end();
	auto targetEnd = settings.TargetIterator.end();
	
	
	auto dist = GetDist(source, target);
	
	while (source != sourceEnd && target != targetEnd)
	{
		auto currDist = GetDist(source, target);
		
		if (currDist != dist && !settings.AllowGap)
		{
			return false;
		}
	}
	
	return false;
}
