#include "Aligner.h"


using namespace Steele;


Aligner::Aligner(const Area& source, const Area &target): 
	m_target(target),
	m_source(source)
{
	
}

int Aligner::GetDiff(outline_scalar_iterator &left, outline_scalar_iterator &right)
{
	
	int diff;
	
	diff = (*left) - (*right);
	
	left++;
	right++;
	
	return diff;
}

bool Aligner::Align(const AlignSettings& settings, Alignment& result) 
{
	result.IsSuccessful = true;
	
	auto dir = settings.AlignmentDirection;
	
	auto source = settings.SourceIterator.begin();
	auto target = settings.TargetIterator.begin();
	auto sourceEnd = settings.SourceIterator.end();
	auto targetEnd = settings.TargetIterator.end();
	
	if (source == sourceEnd || target == targetEnd)
	{
		result.IsSuccessful = false;
		return false;
	}
	
	auto dist = GetDiff(source, target);
	
	while (source != sourceEnd && target != targetEnd)
	{
		auto currDist = GetDiff(source, target);
		
		if (currDist != dist)
		{
			if (!settings.AllowGap)
			{
				result.IsSuccessful = false;
				return false;
			}
			
			if (dir == Direction::North || dir == Direction::East)
			{
				dist = max(dist, currDist);
			}
			else
			{
				dist = min(dist, currDist);
			}
		}
	}
	
	if (settings.Positioning == Align::AlignSettings::Touch)
	{
		if (dir == Direction::North || dir == Direction::East)
		{
			dist += 1;
		}
		else
		{
			dist -= 1;
		}
	}
	
	if (dir == Direction::North || dir == Direction::South)
	{
		result.Offset = v2i(0, dist);
	}
	else
	{
		result.Offset = v2i(dist, 0);
	}
	
	result.Offset += settings.AlignmentVector;
	
	return true;
}


bool Aligner::AdjacentLeftTop(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_left(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_r_right(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::West,
			.AlignmentVector	= { 0, m_source.Top() - m_target.Top() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentLeftBottom(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_left(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_right(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::West,
			.AlignmentVector	= { 0, m_source.Bottom() - m_target.Bottom() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentRightTop(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_right(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_r_left(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::East,
			.AlignmentVector	= { 0, m_source.Top() - m_target.Top() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentRightBottom(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_right(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_left(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::East,
			.AlignmentVector	= { 0, m_source.Bottom() - m_target.Bottom() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentTopLeft(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_top(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_bottom(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::North,
			.AlignmentVector	= { m_source.Left() - m_target.Left(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentTopRight(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_top(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_r_bottom(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::North,
			.AlignmentVector	= { m_source.Right() - m_target.Right(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentBottomLeft(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_bottom(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_top(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::South,
			.AlignmentVector	= { m_source.Left() - m_target.Left(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::AdjacentBottomRight(Alignment &result)
{
	
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_bottom(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_r_top(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Touch,
			.AlignmentDirection = Direction::South,
			.AlignmentVector	= { m_source.Right() - m_target.Right(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideLeftTop(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_left(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_r_left(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::East,
			.AlignmentVector	= { 0, m_source.Top() - m_target.Top() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideLeftBottom(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_left(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_left(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::East,
			.AlignmentVector	= { 0, m_source.Bottom() - m_target.Bottom() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideRightTop(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_right(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_r_right(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::West,
			.AlignmentVector	= { 0, m_source.Top() - m_target.Top() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideRightBottom(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_right(), Axis::X }, 
			.TargetIterator =  { m_target.iterate_right(), Axis::X },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::West,
			.AlignmentVector	= { 0, m_source.Bottom() - m_target.Bottom() },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideTopLeft(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_top(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_top(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::South,
			.AlignmentVector	= { m_source.Left() - m_target.Left(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideTopRight(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_top(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_r_top(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::South,
			.AlignmentVector	= { m_source.Right() - m_target.Right(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideBottomLeft(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_bottom(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_bottom(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::North,
			.AlignmentVector	= { m_source.Left() - m_target.Left(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}

bool Aligner::InsideBottomRight(Alignment &result)
{
	return Align(
		AlignSettings {
			.Source	= m_source,
			.Target = m_target,
			
			.SourceIterator =  { m_source.iterate_r_bottom(), Axis::Y }, 
			.TargetIterator =  { m_target.iterate_r_bottom(), Axis::Y },
			
			.Positioning		= Align::AlignSettings::Overlap,
			.AlignmentDirection = Direction::North,
			.AlignmentVector	= { m_source.Right() - m_target.Right(), 0 },
			
			.AllowGap			= m_allowGap
		},
		result
	);
}
