#ifndef STEELE_IMAP_H
#define STEELE_IMAP_H


#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector3i.hpp>

#include <string>

#include "DataTypes/Types.h"


namespace Steele
{
	template <typename CELL>
	class IMap
	{
	protected:
		virtual CELL* _try_get(v3i at) = 0;
		virtual const CELL* _try_get(v3i at) const = 0;
		virtual CELL* _get(v3i at) = 0;
		
		virtual void _set(const CELL& c, v3i at) = 0;
		virtual void _set(CELL&& c, v3i at) = 0;
		
		virtual bool _is_empty(v3i at) const = 0;
		virtual bool _remove(v3i at) = 0;
		
		
	public:
		virtual size_t size() const = 0;
		
		
	public:
		inline CELL* get(int x, int y)			{ return _get({x, y, 0}); }
		inline CELL* get(int x, int y, int z)	{ return _get({x, y, z}); }
		inline CELL* get(v2i at)				{ return _get({at.x, at.y, 0}); }
		inline CELL* get(v2i at, int z)			{ return _get({at.x, at.y, z}); }
		inline CELL* get(v3i at)				{ return _get(at); }
		
		inline CELL* try_get(int x, int y) 			{ return _try_get({x, y, 0}); };
		inline CELL* try_get(int x, int y, int z) 	{ return _try_get({x, y, z}); };
		inline CELL* try_get(v2i at) 				{ return _try_get({at.x, at.y, 0}); };
		inline CELL* try_get(v2i at, int z) 		{ return _try_get({at.x, at.y, z}); };
		inline CELL* try_get(v3i at) 				{ return _try_get(at); };
		
		inline bool try_get(int x, int y, CELL** c) 		{ (*c) = _try_get({x, y, 0}); return (bool)(*c); };
		inline bool try_get(int x, int y, int z, CELL** c) 	{ (*c) = _try_get({x, y, z}); return (bool)(*c); };
		inline bool try_get(v2i at, CELL** c) 				{ (*c) = _try_get({at.x, at.y, 0}); return (bool)(*c); };
		inline bool try_get(v2i at, int z, CELL** c) 		{ (*c) = _try_get({at.x, at.y, z}); return (bool)(*c); };
		inline bool try_get(v3i at, CELL** c) 				{ (*c) = _try_get(at); return (bool)(*c); };
		
		inline const CELL* try_get(int x, int y) const 			{ return _try_get({x, y, 0}); };
		inline const CELL* try_get(int x, int y, int z) const  	{ return _try_get({x, y, z}); };
		inline const CELL* try_get(v2i at) const				{ return _try_get({at.x, at.y, 0}); };
		inline const CELL* try_get(v2i at, int z) const			{ return _try_get({at.x, at.y, z}); };
		inline const CELL* try_get(v3i at) const				{ return _try_get(at); };
		
		inline bool try_get(int x, int y, const CELL** c) const 		{ (*c) = _try_get({x, y, 0}); return (bool)(*c); };
		inline bool try_get(int x, int y, int z, const CELL** c) const 	{ (*c) = _try_get({x, y, z}); return (bool)(*c); };
		inline bool try_get(v2i at, const CELL** c) const				{ (*c) = _try_get({at.x, at.y, 0}); return (bool)(*c); };
		inline bool try_get(v2i at, int z, const CELL** c) const		{ (*c) = _try_get({at.x, at.y, z}); return (bool)(*c); };
		inline bool try_get(v3i at, const CELL** c) const				{ (*c) = _try_get(at); return (bool)(*c); };
		
		inline bool is_empty(int x, int y) const 		{ return _is_empty({x, y, 0}); }
		inline bool is_empty(int x, int y, int z) const { return _is_empty({x, y, z}); }
		inline bool is_empty(v2i at) const 				{ return _is_empty({at.x, at.y, 0}); }
		inline bool is_empty(v2i at, int z) const 		{ return _is_empty({at.x, at.y, z}); }
		inline bool is_empty(v3i at) const 				{ return _is_empty(at); }
		
		inline bool remove(int x, int y)		{ return _remove({x, y, 0}); }
		inline bool remove(int x, int y, int z)	{ return _remove({x, y, z}); }
		inline bool remove(v2i at)				{ return _remove({at.x, at.y, 0}); }
		inline bool remove(v2i at, int z)		{ return _remove({at.x, at.y, z}); }
		inline bool remove(v3i at)				{ return _remove(at); }
		
		inline void set(const CELL& c, int x, int y)		{ return _set(c, {x, y, 0}); }
		inline void set(const CELL& c, int x, int y, int z)	{ return _set(c, {x, y, z}); }
		inline void set(const CELL& c, v2i at) 				{ return _set(c, {at.x, at.y, 0}); }
		inline void set(const CELL& c, v2i at, int z)		{ return _set(c, {at.x, at.y, z}); }
		inline void set(const CELL& c, v3i at)				{ return _set(c, at); }
		
		inline void set(CELL&& c, int x, int y)			{ return _set(c, {x, y, 0}); }
		inline void set(CELL&& c, int x, int y, int z)	{ return _set(c, {x, y, z}); }
		inline void set(CELL&& c, v2i at) 				{ return _set(c, {at.x, at.y, 0}); }
		inline void set(CELL&& c, v2i at, int z) 		{ return _set(c, {at.x, at.y, z}); }
		inline void set(CELL&& c, v3i at) 				{ return _set(c, at); }
		
		
	public:
		virtual void clear() = 0;
	};
}


#endif