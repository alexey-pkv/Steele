#ifndef STEELE_GENMAP_H
#define STEELE_GENMAP_H


#include "../Utils.h"
#include "../IMap.h"
#include "../DataTypes/Direction.h"
#include "GenCell.h"

#include <godot_cpp/variant/vector2i.hpp>

#include <vector>


using namespace godot;


namespace Steele
{
	class GenMap
	{
	private:
		struct _offset
		{
			Vector2i position;
			Direction rotation;
		};
	private:
		
		Vector2i m_offset;
		Direction m_rotation;
		
		std::vector<_offset> m_offsetStuck;
		
	public:
		void Checkpoint();
		void Rollback();
		void Commit();
		
		void PushOffset(const Vector2i& by, Direction d);
		void PopOffset();
		bool HasOffset() const;
		Direction GetOffsetDirection() const;
		Vector2i GetOffsetPosition() const;
		
		GenCell Get(const Vector2i& at) const;
		GenCell Get(int x, int y) const;
		
		void Set(const Vector2i& at, const GenCell& val);
		void Set(int x, int y, const GenCell& at) const;
	};
}


#endif