#ifndef STEEL_ENGINE_DIRECTION_H
#define STEEL_ENGINE_DIRECTION_H


#include <string>
#include <iostream>

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/vector3i.hpp>


namespace Steele
{
	const char DIRECTION_MASK		= 0b0111;
	const char DIRECTION_ROUND_MASK	= 0b0110;
	const int DIRECTIONS_COUNT		= 8;
	
	
	enum class DirectionValue : char
	{
		North		= 0b0000,
		NorthEast	= 0b0001,
		East		= 0b0010,
		SouthEast	= 0b0011,
		South		= 0b0100,
		SouthWest	= 0b0101,
		West		= 0b0110,
		NorthWest	= 0b0111,
	};
	
	
	class Direction
	{
	private:
		DirectionValue m_direction = DirectionValue::North;
		
		
	private:
		static const char* m_directionStrings[];
		
		
	private:
		static DirectionValue to_dir(int val) { return (DirectionValue)(val & DIRECTION_MASK); }
		
		
	public:
		Direction() = default;
		Direction(const Direction&) = default;
		Direction(Direction&&) = default;
		Direction& operator= (const Direction& fraction) = default;
		Direction& operator= (Direction&& fraction) = default;
		
		explicit Direction(int i): m_direction(to_dir(i)) {};
		explicit Direction(DirectionValue dv): m_direction(dv) {};
		
		inline explicit operator const char*() const { return m_directionStrings[((int)m_direction & DIRECTION_MASK)]; }
		inline explicit operator std::string() const { return { (char*)this }; }
		
		inline explicit operator int8_t () const { return (int8_t)m_direction; }
		inline explicit operator int16_t () const { return (int16_t)m_direction; }
		inline explicit operator int32_t () const { return (int32_t)m_direction; }
		inline explicit operator int64_t () const { return (int64_t)m_direction; }
		inline explicit operator uint8_t () const { return (uint8_t)m_direction; }
		inline explicit operator uint16_t () const { return (uint16_t)m_direction; }
		inline explicit operator uint32_t () const { return (uint32_t)m_direction; }
		inline explicit operator uint64_t () const { return (uint64_t)m_direction; }
		
		inline Direction operator++() { return Direction((int)(m_direction) + 1); }
		inline Direction operator--() { return m_direction == DirectionValue::North ? Direction::NorthWest : Direction((int)(m_direction) - 1); }
		
		inline Direction operator+(Direction d) const { return Direction((int)(m_direction) + (int)d.m_direction); }
		inline Direction operator-(Direction d) const { return Direction(DIRECTIONS_COUNT + (int)(m_direction) - (int)d.m_direction);}
		inline Direction operator*(int by) { return Direction(((int)m_direction) * by);}
		
		inline void operator+=(Direction d) { m_direction = to_dir((int)(m_direction) + (int)d.m_direction); }
		inline void operator-=(Direction d) { m_direction = to_dir(DIRECTIONS_COUNT + (int)(m_direction) - (int)d.m_direction);}
		inline void operator*=(int by) { m_direction = to_dir(((int)m_direction) * by);}
		
		
		inline bool operator==(Direction to) { return m_direction == to.m_direction; }
		inline bool operator!=(Direction to) { return m_direction != to.m_direction; }
		
		godot::Vector2 Rotate(const godot::Vector2& source) const;
		godot::Vector2i Rotate(const godot::Vector2i& source) const;
		
		godot::Vector3 Rotate(const godot::Vector3& source) const;
		godot::Vector3i Rotate(const godot::Vector3i& source) const;
		
		void RotateInPlace(godot::Vector2& source) const;
		void RotateInPlace(godot::Vector2i& source) const;
		
		void RotateInPlace(godot::Vector3& source) const;
		void RotateInPlace(godot::Vector3i& source) const;
		
		
	public:
		static const Direction North;  
		static const Direction NorthEast;
		static const Direction East;
		static const Direction SouthEast;
		static const Direction South;
		static const Direction SouthWest;
		static const Direction West;
		static const Direction NorthWest;
	};
	
	
	inline std::ostream& operator<<(std::ostream &os, Direction d) { return os << (const char*)d; }
	
	inline godot::Vector2 operator*(const godot::Vector2& v, Direction d) { return d.Rotate(v); }
	inline godot::Vector2i operator*(const godot::Vector2i& v, Direction d) { return d.Rotate(v); }
	inline godot::Vector3 operator*(const godot::Vector3& v, Direction d) { return d.Rotate(v); }
	inline godot::Vector3i operator*(const godot::Vector3i& v, Direction d) { return d.Rotate(v); }
	
	inline godot::Vector2& operator*=(godot::Vector2& v, Direction d) { d.RotateInPlace(v); return v; }
	inline godot::Vector2i& operator*=(godot::Vector2i& v, Direction d) { d.RotateInPlace(v); return v; }
	inline godot::Vector3& operator*=(godot::Vector3& v, Direction d) { d.RotateInPlace(v); return v; }
	inline godot::Vector3i& operator*=(godot::Vector3i& v, Direction d) { d.RotateInPlace(v); return v; }
}


#endif