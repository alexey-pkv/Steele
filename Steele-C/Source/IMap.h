#ifndef STEELE_IMAP_H
#define STEELE_IMAP_H


#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector3i.hpp>
#include "DataTypes/Transformation.h"
#include "Map/Cell.h"


namespace Steele
{
	template <typename CELL>
	class IMap
	{
	public:
		virtual CELL Get_v3(const godot::Vector3i& at) = 0;
		virtual void Set_v3(const CELL& cell, const godot::Vector3i& at) = 0;
		virtual bool IsEmpty_v3(const godot::Vector3i& at) = 0;
		virtual bool Remove_v3(const godot::Vector3i& at) = 0;
		
		
		inline CELL Get(int x, int y, int z) { return Get_v3({x, y, z}); }
		inline CELL Get_v2z(const godot::Vector2i& at, int z) { return Get({at.x, at.y, z}); }
		inline void Set(const CELL& cell, int x, int y, int z) { Set_v3(cell, {x, y, z}); }
		inline void Set_v2z(const CELL& cell, const godot::Vector2i& at, int z) { Set(cell, {at.x, at.y, z}); }
		inline bool IsEmpty(int x, int y, int z) { return IsEmpty_v3({x, y, z}); }
		inline bool IsEmpty_v2z(const godot::Vector2i& at, int z) { return IsEmpty_v3({at.x, at.y, z}); }
		inline bool Remove(int x, int y, int z) { return Remove_v3({x, y, z}); }
		inline bool Remove_v2z(const godot::Vector2i& at, int z) { return Remove_v3({at.x, at.y, z}); }
		
		
	public:
		inline void PushTransformation_v3d(const godot::Vector3i& t, Direction dir) { PushTransformation({ .Dir = dir, .Offset = t }); }
		
		
	public:
		virtual void PushTransformation(const Transformation& t) = 0;
		virtual bool PopTransformation() = 0;
	};
	
	
	typedef IMap<Cell> ICellMap; 
}


#endif