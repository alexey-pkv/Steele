#ifndef STEELE_TOTEM_H
#define STEELE_TOTEM_H


#include "DataTypes/Types.h"

namespace Steele
{
	struct Totem
	{
	public:
		enum class Style : char
		{
			Square	= 's',
			Circle	= 'c',
			Rhombus	= 'r',
		};
		
		enum class Status : char
		{
			Active	= 'a',
			Loading	= 'l'
		};
		
		
	private:
		bool contains(v3i point, int dist) const;
		
		
	public:
		v3i At = v3i_zero;
		
		Style	RadiusStyle			= Style::Rhombus;
		Status	TotemStatus			= Status::Loading;
		
		int		ActiveRadius		= 0;
		int		StandbyRadius		= 1;
		int		CacheRadius			= 2;
		
		
	public:
		inline bool contains_active(v3i point) const { return contains(point, ActiveRadius); }
		inline bool contains_standby(v3i point) const { return contains(point, StandbyRadius); }
		inline bool contains_cache(v3i point) const { return contains(point, CacheRadius); }
	};
}


#endif