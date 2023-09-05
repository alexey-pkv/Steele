#ifndef STEELE_AREA_H
#define STEELE_AREA_H


#include <vector>

#include "Types.h"
#include "Direction.h"
#include "godot_cpp/variant/rect2i.hpp"


using namespace std;
using namespace godot;


namespace Steele
{
	class Area
	{
	private:
		class AreaLine
		{
		private:
			vector<v2i>	m_line;
		
		
		public:
			struct Iterator
			{
			public:
				int CurrCoord	= -1;
				
				vector<v2i>::const_iterator CurrIndex;
				vector<v2i>::const_iterator End;
				
			public:
				inline int operator*() const { return CurrCoord; }
				bool operator!=(const Iterator& to) const { return to.CurrCoord != CurrCoord; }
				bool operator==(const Iterator& to) const { return to.CurrCoord == CurrCoord; }
			
			public:
				void operator++(int);
			};
		
		
		public:
			explicit AreaLine(v2i v);
			
			AreaLine() = default;
			AreaLine(const AreaLine&) = default;
			AreaLine(AreaLine&&) = default;
			AreaLine& operator=(const AreaLine&) = default;
			AreaLine& operator=(AreaLine&&) = default;
			
			~AreaLine() = default;
			
		public:
			bool contains(int y) const;
			bool contains(const v2i& v) const;
			bool contains(const AreaLine& yva) const;
			
			bool overlaps(const v2i& v) const;
			bool overlaps(const AreaLine& yva) const;
			
			void flip(int offset);
			
			uint64_t area() const;
			bool is_empty() const;
			
			int min() const;
			int max() const;
			
			void clear();
		
		public:
			inline AreaLine operator|(int with) const				{ auto v = AreaLine(*this); v |= with; return v; }
			inline AreaLine operator|(const v2i& with) const		{ auto v = AreaLine(*this); v |= with; return v; }
			inline AreaLine operator|(const AreaLine& yva) const	{ auto v = AreaLine(*this); v |= yva; return v; }
			inline AreaLine operator-(int with) const				{ auto v = AreaLine(*this); v -= with; return v; }
			inline AreaLine operator-(const v2i& with) const		{ auto v = AreaLine(*this); v -= with; return v; }
			inline AreaLine operator-(const AreaLine& yva) const	{ auto v = AreaLine(*this); v -= yva; return v; }
			inline AreaLine operator&(int with) const				{ auto v = AreaLine(*this); v &= with; return v; }
			inline AreaLine operator&(const v2i& with) const		{ auto v = AreaLine(*this); v &= with; return v; }
			inline AreaLine operator&(const AreaLine& yva) const	{ auto v = AreaLine(*this); v &= yva; return v; }
			inline AreaLine operator>>(int by) const				{ auto v = AreaLine(*this); v >>= by; return v; }
			inline AreaLine operator<<(int by) const				{ auto v = AreaLine(*this); v <<= by; return v; }
			
			inline void operator|=(int with) { (*this) |= AreaLine({with, with }); }
			inline void operator-=(int with) { (*this) -= AreaLine({with, with }); }
			inline void operator|=(const v2i& with) { (*this) |= AreaLine(with); };
			inline void operator-=(const v2i& with) { (*this) -= AreaLine(with); };
			inline void operator&=(const v2i& with) { (*this) &= AreaLine(with); };
			
			void operator&=(int with);
			void operator|=(const AreaLine& yva);
			void operator-=(const AreaLine& yva);
			void operator&=(const AreaLine& yva);
			
			void operator>>=(int by);
			void operator<<=(int by);
			
			bool operator&&(const AreaLine& yva) const;
			
		public:
			Iterator begin() const; 
			Iterator end() const;
		
		public:
			inline bool operator==(const AreaLine& b) const { return m_line == b.m_line; };
			inline bool operator!=(const AreaLine& b) const { return m_line != b.m_line; };
		};
		
	public:
		struct iterator
		{
		public:
			int		XOffset = 0;
			int		Index = 0;
			
			AreaLine::Iterator Inner;
			AreaLine::Iterator InnerEnd;
			
			vector<AreaLine>::const_iterator Primary;
			vector<AreaLine>::const_iterator PrimaryEnd;
			
		public:
			inline v2i operator*() const { return {XOffset + Index, *Inner}; }
			inline bool operator!=(const iterator& to) const { return to.Primary != Primary || to.Inner != Inner; }
			inline bool operator==(const iterator& to) const { return to.Primary == Primary && to.Inner == Inner; }
			
		
		public:
			void operator++();
		};
		
		
		struct outline_iterator
		{
		public:
			int Offset		= 0;
			int Index		= 0;
			int Direction	= 1;
			
			enum IterationStyle
			{
				LEFT,
				RIGHT,
				BOTTOM, 
				TOP
			} Style = LEFT;
			
			const vector<AreaLine>& Source;
			
			
		public:
			outline_iterator(const outline_iterator&) = default;
			outline_iterator(outline_iterator&&) = default;
			
			outline_iterator(const vector <AreaLine>& source, int offset, int direction, int index, IterationStyle style);
			
			
		public:
			inline bool operator!=(const outline_iterator& to) const { return to.Index != Index; }
			inline bool operator==(const outline_iterator& to) const { return to.Index == Index; }
			inline void operator++() { Offset += Direction; Index += Direction; }
			inline void operator++(int) { Offset += Direction; Index += Direction; }
			
			
		public:
			v2i operator*() const;
		};
		
		
		struct outline_iterator_provider
		{
		private:
			int m_offset;
			int m_direction;
			
			const vector<AreaLine>&				m_lines;
			outline_iterator::IterationStyle	m_style;
			
			
			inline int GetBeginIndex() const { return m_direction == 1 ? 0 : (int)(m_lines.size()) - 1; }
			inline int GetEndIndex() const { return m_direction == 1 ? (int)(m_lines.size()) : -1; }
			
		public:
			outline_iterator_provider(const outline_iterator_provider&) = default;
			outline_iterator_provider(outline_iterator_provider&&) = default;
			outline_iterator_provider(const vector<AreaLine>&, int, outline_iterator::IterationStyle, bool isReverse = false);
			
		public:
			inline outline_iterator begin() const { return {m_lines, m_offset, m_direction, GetBeginIndex() , m_style }; }
			inline outline_iterator end() const { return {m_lines, m_offset, m_direction, GetEndIndex(), m_style }; }
		};
		
		
	private:
		v2i					m_offset;
		vector<AreaLine>	m_vertical;
		vector<AreaLine>	m_horizontal;
		
		
	private:
		void clear();
		void clean_up();
		
		
	private:
		static void offset_all(vector<AreaLine>& lines, int by);
		static void flip_lines(vector<AreaLine>& lines, int offset);
		
		static int merge_vectors_begin(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		static void merge_vectors_overlapping(int oa, int offset, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		static void merge_vectors_end(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		
		static int subtract_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		static int intersect_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		static int merge_vectors(int oa, vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		
		static v2i get_common_range(int oa, const vector<Area::AreaLine>& a, int ob, const vector<Area::AreaLine>& b);
		
		static int clean_up(vector<Area::AreaLine> &a);
		
		
	public:
		~Area() = default;
		
		Area() = default;
		Area(const Area&) = default;
		Area(Area&&) = default;
		Area& operator=(const Area&) = default;
		Area& operator=(Area&&) = default;
		
		explicit Area(Rect2i r);
		explicit Area(const std::string& area_template);
		Area(int x, int y, int to_x, int to_y);
		Area(int x_at, int y_at);
		
		
	public:
		inline bool operator==(const Area& b) const { return m_offset == b.m_offset && m_vertical == b.m_vertical; };
		inline bool operator!=(const Area& b) const { return m_offset != b.m_offset || m_vertical != b.m_vertical; };
		inline Area& operator-=(const Vector2i& v) { return *this += -v; };
		
		inline Area operator|(const Area& a) const { return (Area(*this) |= a); }
		inline Area operator&(const Area& a) const { return (Area(*this) &= a); }
		inline Area operator-(const Area& a) const { return (Area(*this) -= a); }
		inline Area operator^(const Area& a) const { return (*this | a) - (*this & a); }
		inline Area operator*(Direction dir) const { return (Area(*this) *= dir); }
		
		
		bool operator&&(const Area& a) const;
		
		
		inline Area operator+(const v2i& v) const { return (Area(*this) += v); }
		inline Area operator-(const v2i& v) const { return (Area(*this) += v); }
		
		Area& operator+=(const Vector2i& v);
		Area& operator*=(Direction dir);
		
		Area& operator|=(const Area& a);
		Area& operator&=(const Area& a);
		Area& operator-=(const Area& a);
		
		inline Area& operator^=(const Area& a) { return *this = *this ^ a;}
		
		bool operator[](v2i at);
		
		inline bool operator< (const Area& a) const { return (*this <= a && this->get_area() != a.get_area()); }
		inline bool operator> (const Area& a) const { return (*this >= a && this->get_area() != a.get_area()); }
		inline bool operator<=(const Area& a) const { return a >= *this; }
		bool operator>=(const Area& a) const;
		
		
	public:
		uint64_t get_area() const;
		
		bool contains(const v2i& v) const;
		
		
	public:
		inline int height() const	{ return (int)m_horizontal.size(); }
		inline int width() const	{ return (int)m_vertical.size(); }
		inline int top() const		{ return m_offset.y + (int)m_horizontal.size() - 1; }
		inline int bottom() const	{ return m_offset.y; }
		inline int right() const	{ return m_offset.x + (int)m_vertical.size() - 1; }
		inline int left() const		{ return m_offset.x; }
		
		inline int x() const { return m_offset.x; }
		inline int y() const { return m_offset.y; }
		inline v2i offset() const	{ return m_offset; }
		inline bool is_empty() const { return m_vertical.empty(); }
		
		inline void set_offset(int x, int y) { set_offset({x, y}); }
		inline void set_offset(v2i v) { *this += (v - m_offset); }
		inline void reset_offset() { *this -= m_offset; }
		
		inline Rect2i GetRect() const
		{
			return 
			{ 
				{left(),                 bottom() }, 
				{(int)m_vertical.size(), (int)m_horizontal.size()} 
			}; 
		}
		
		
	public:
		string debug_info(char fill = '*', char empty = '.', bool withBoarder = true) const;
		
		
	public:
		iterator begin() const;
		iterator end() const;
		
		inline outline_iterator_provider iterate_top() const	{ return { m_vertical, m_offset.x, outline_iterator::IterationStyle::TOP }; }
		inline outline_iterator_provider iterate_bottom() const	{ return { m_vertical, m_offset.x, outline_iterator::IterationStyle::BOTTOM }; }
		inline outline_iterator_provider iterate_left() const	{ return { m_horizontal, m_offset.y, outline_iterator::IterationStyle::LEFT }; }
		inline outline_iterator_provider iterate_right() const	{ return { m_horizontal, m_offset.y, outline_iterator::IterationStyle::RIGHT }; }
		
		inline outline_iterator_provider iterate_r_top() const	{ return { m_vertical, m_offset.x, outline_iterator::IterationStyle::TOP, true }; }
		inline outline_iterator_provider iterate_r_bottom() const	{ return { m_vertical, m_offset.x, outline_iterator::IterationStyle::BOTTOM, true }; }
		inline outline_iterator_provider iterate_r_left() const	{ return { m_horizontal, m_offset.y, outline_iterator::IterationStyle::LEFT, true }; }
		inline outline_iterator_provider iterate_r_right() const	{ return { m_horizontal, m_offset.y, outline_iterator::IterationStyle::RIGHT, true }; }
	};
}

namespace std
{
	template<>
	struct hash<v2i>
	{
		std::size_t operator()(const v2i& v) const
		{
			return hash<int>()(v.x) ^ hash<int>()(v.y << 1);
		}
	};
	
	template<>
	struct hash<Rect2i>
	{
		std::size_t operator()(const Rect2i& r) const
		{
			return hash<v2i>()(r.position) ^ hash<v2i>()(r.size);
		}
	};
	
	template<>
	struct hash<Steele::Area>
	{
		std::size_t operator()(const Steele::Area& area) const
		{
			size_t val = std::hash<Rect2i>()(area.GetRect());
			
			val ^= hash<uint64_t>()(area.get_area());
			
			for (const auto& a : area)
			{
				val ^= hash<v2i>()(a);
			}
			
			return val;
		}
	};
}


#endif