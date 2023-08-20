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
		static int GetDiff(outline_scalar_iterator& left, outline_scalar_iterator& right);
		static bool Align(const AlignSettings& settings, Alignment& result) ;
		
		
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
		
		bool InsideLeftTop(Alignment& result);
		bool InsideLeftBottom(Alignment& result);
		bool InsideRightTop(Alignment& result);
		bool InsideRightBottom(Alignment& result);
		bool InsideTopLeft(Alignment& result);
		bool InsideTopRight(Alignment& result);
		bool InsideBottomLeft(Alignment& result);
		bool InsideBottomRight(Alignment& result);
		
		
		inline Alignment AdjacentLeftTop()		{ Alignment a; this->AdjacentLeftTop(a); return a; }
		inline Alignment AdjacentLeftBottom()	{ Alignment a; this->AdjacentLeftBottom(a); return a; }
		inline Alignment AdjacentRightTop()		{ Alignment a; this->AdjacentRightTop(a); return a; }
		inline Alignment AdjacentRightBottom()	{ Alignment a; this->AdjacentRightBottom(a); return a; }
		inline Alignment AdjacentTopLeft()		{ Alignment a; this->AdjacentTopLeft(a); return a; }
		inline Alignment AdjacentTopRight()		{ Alignment a; this->AdjacentTopRight(a); return a; }
		inline Alignment AdjacentBottomLeft()	{ Alignment a; this->AdjacentBottomLeft(a); return a; }
		inline Alignment AdjacentBottomRight()	{ Alignment a; this->AdjacentBottomRight(a); return a; }
		
		inline Alignment InsideLeftTop()		{ Alignment a; this->InsideLeftTop(a); return a; }
		inline Alignment InsideLeftBottom()		{ Alignment a; this->InsideLeftBottom(a); return a; }
		inline Alignment InsideRightTop()		{ Alignment a; this->InsideRightTop(a); return a; }
		inline Alignment InsideRightBottom()	{ Alignment a; this->InsideRightBottom(a); return a; }
		inline Alignment InsideTopLeft()		{ Alignment a; this->InsideTopLeft(a); return a; }
		inline Alignment InsideTopRight()		{ Alignment a; this->InsideTopRight(a); return a; }
		inline Alignment InsideBottomLeft()		{ Alignment a; this->InsideBottomLeft(a); return a; }
		inline Alignment InsideBottomRight()	{ Alignment a; this->InsideBottomRight(a); return a; }
		
		
	public:
		static inline bool AdjacentLeftTop(const Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).AdjacentLeftTop(result); }
		static inline bool AdjacentLeftBottom(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentLeftBottom(result); }
		static inline bool AdjacentRightTop(const Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).AdjacentRightTop(result); }
		static inline bool AdjacentRightBottom(const Area& source, const Area& target, Alignment& result)	{ return Aligner(source, target).AdjacentRightBottom(result); }
		static inline bool AdjacentTopLeft(const Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).AdjacentTopLeft(result); }
		static inline bool AdjacentTopRight(const Area& source, const Area& target, Alignment& result) 		{ return Aligner(source, target).AdjacentTopRight(result); }
		static inline bool AdjacentBottomLeft(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).AdjacentBottomLeft(result); }
		static inline bool AdjacentBottomRight(const Area& source, const Area& target, Alignment& result)	{ return Aligner(source, target).AdjacentBottomRight(result); }
		
		static inline bool InsideLeftTop(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideLeftTop(result); }
		static inline bool InsideLeftBottom(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideLeftBottom(result); }
		static inline bool InsideRightTop(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideRightTop(result); }
		static inline bool InsideRightBottom(const Area& source, const Area& target, Alignment& result)	{ return Aligner(source, target).InsideRightBottom(result); }
		static inline bool InsideTopLeft(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideTopLeft(result); }
		static inline bool InsideTopRight(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideTopRight(result); }
		static inline bool InsideBottomLeft(const Area& source, const Area& target, Alignment& result) 	{ return Aligner(source, target).InsideBottomLeft(result); }
		static inline bool InsideBottomRight(const Area& source, const Area& target, Alignment& result) { return Aligner(source, target).InsideBottomRight(result); }
		
		static inline Alignment AdjacentLeftTop(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentLeftTop(result); return result; }
		static inline Alignment AdjacentLeftBottom(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentLeftBottom(result); return result; }
		static inline Alignment AdjacentRightTop(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentRightTop(result); return result; }
		static inline Alignment AdjacentRightBottom(const Area& source, const Area& target)	{ Alignment result; Aligner(source, target).AdjacentRightBottom(result); return result; }
		static inline Alignment AdjacentTopLeft(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentTopLeft(result); return result; }
		static inline Alignment AdjacentTopRight(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentTopRight(result); return result; }
		static inline Alignment AdjacentBottomLeft(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).AdjacentBottomLeft(result); return result; }
		static inline Alignment AdjacentBottomRight(const Area& source, const Area& target)	{ Alignment result; Aligner(source, target).AdjacentBottomRight(result); return result; }
		
		static inline Alignment InsideLeftTop(const Area& source, const Area& target) 		{ Alignment result; Aligner(source, target).InsideLeftTop(result); return result; }
		static inline Alignment InsideLeftBottom(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).InsideLeftBottom(result); return result; }
		static inline Alignment InsideRightTop(const Area& source, const Area& target) 		{ Alignment result; Aligner(source, target).InsideRightTop(result); return result; }
		static inline Alignment InsideRightBottom(const Area& source, const Area& target)	{ Alignment result; Aligner(source, target).InsideRightBottom(result); return result; }
		static inline Alignment InsideTopLeft(const Area& source, const Area& target) 		{ Alignment result; Aligner(source, target).InsideTopLeft(result); return result; }
		static inline Alignment InsideTopRight(const Area& source, const Area& target) 		{ Alignment result; Aligner(source, target).InsideTopRight(result); return result; }
		static inline Alignment InsideBottomLeft(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).InsideBottomLeft(result); return result; }
		static inline Alignment InsideBottomRight(const Area& source, const Area& target) 	{ Alignment result; Aligner(source, target).InsideBottomRight(result); return result; }
	};
}


#endif