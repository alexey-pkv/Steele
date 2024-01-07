#ifndef STEELE_REGION_H
#define STEELE_REGION_H


#include "Utils.h"

#include "DataTypes/Types.h"
#include "DataTypes/Map/Cell.h"


namespace Steele
{
	struct Region
	{
	public:
		enum class LoadState : char
		{
			Active,
			Location,
			Inactive
		};
		
		
	public:
		v3i					Index		= v3i_zero;
		v3i 				Offset		= v3i_zero;
		LoadState			State		= LoadState::Inactive;
		vec<t_id>			Locations	= {};
		bool				IsLoaded	= false;
		std::map<v3i, Cell>	Map;
		
		
	public:
		~Region() = default;
		Region() = default;
		Region(const Region&) = default;
		Region(Region&&) = default;
		Region& operator=(const Region&) = default;
		Region& operator=(Region&&) = default;
		
		Region(v3i index, v3i size);
		
		
	public:
		void set_dimensions(v3i index, v3i size);
	};
}


#endif