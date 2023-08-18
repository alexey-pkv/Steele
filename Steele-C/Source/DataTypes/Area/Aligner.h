#ifndef STEELE_ALIGNER_H
#define STEELE_ALIGNER_H


#include "DataTypes/Area.h"

#include "Alignment.h"
#include "AlignSettings.h"


using namespace Steele::Align;


namespace Steele
{
	class Aligner
	{
	private:
		const Area& m_source;
		const Area& m_target;
		
		bool	m_allowGap = true;
		
		
	private:
		int GetDist(outline_scalar_iterator& source, outline_scalar_iterator& target);
		bool Align(AlignSettings& settings, Alignment& result);
		
		
	public:
		~Aligner() = default;
		Aligner(const Aligner&) = default;
		Aligner(Aligner&&) = default;
		
		Aligner(const Area& source, const Area& target);
		
		
	public:
		inline void AllowGap() { m_allowGap = true; }
		inline void NoGap() { m_allowGap = false; }
		
		
	public:
		bool AdjacentLeftTop(Alignment& result);
		bool AdjacentLeftBottom(Alignment& result);
		bool AdjacentRightTop(Alignment& result);
		bool AdjacentRightBottom(Alignment& result);
		bool AdjacentTopLeft(Alignment& result);
		bool AdjacentTopRight(Alignment& result);
		bool AdjacentBottomLeft(Alignment& result);
		bool AdjacentBottomRight(Alignment& result);
		
		bool InsideTopLeft(Alignment& result);
		bool InsideTopRight(Alignment& result);
		bool InsideBottomLeft(Alignment& result);
		bool InsideBottomRight(Alignment& result);
		
		
	public:
		static inline bool AdjacentLeftTop(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentLeftTop(result); }
		static inline bool AdjacentLeftBottom(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentLeftBottom(result); }
		static inline bool AdjacentRightTop(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentRightTop(result); }
		static inline bool AdjacentRightBottom(Area& source, const Area& target, Alignment& result) { return Aligner(source, target).AdjacentRightBottom(result); }
		static inline bool AdjacentTopLeft(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentTopLeft(result); }
		static inline bool AdjacentTopRight(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentTopRight(result); }
		static inline bool AdjacentBottomLeft(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentBottomLeft(result); }
		static inline bool AdjacentBottomRight(Area& source, const Area& target, Alignment& result)	{ return Aligner(source, target).AdjacentBottomRight(result); }
		static inline bool InsideTopLeft(Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).InsideTopLeft(result); }
		static inline bool InsideTopRight(Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).InsideTopRight(result); }
		static inline bool InsideBottomLeft(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideBottomLeft(result); }
		static inline bool InsideBottomRight(Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideBottomRight(result); }
	};
}


#endif