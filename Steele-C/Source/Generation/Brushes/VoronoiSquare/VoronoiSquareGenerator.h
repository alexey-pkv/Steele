#ifndef STEELE_VORONOISQUAREGENERATOR_H
#define STEELE_VORONOISQUAREGENERATOR_H


#include "DataTypes/Types.h"
#include "Base/Map/SimpleMap.h"
#include "DataTypes/Area.h"
#include "Base/RNG/IRNG.h"


namespace Steele
{
	class VoronoiSquareGenerator
	{
	private:
		struct CenterInfo
		{
			char 	Sign		= '\0';
			int		Distance	= 0;
			v2i		Center		= v2i_zero;
			bool 	Complete 	= false;
			Area	TotalArea;
		};
		
		
	private:
		v2i 					m_size;
		std::vector<CenterInfo>	m_centers;
		SimpleMap<CenterInfo*>	m_map;
		std::set<int>			m_toFill;
		IRNG*					m_rng;
		
		
	private:
		bool place_centers(int centers);
		bool fill_once_corner(CenterInfo& center, v2i corner);
		bool fill_once_corners(CenterInfo& center);
		bool fill_direction(CenterInfo& center, v2i dir);
		bool fill_once();
		bool fill_once(CenterInfo& center);
		
		
	public:
		bool generate(IRNG& rng, v2i size, int centers);
		bool generate_avg(IRNG& rng, v2i size, int avg_area);
		
		
	public:
		SimpleMap<CenterInfo*>& map() { return m_map; }
		std::vector<CenterInfo>& areas() { return m_centers; }
		
		
	public:
		std::string debug_info() const;
	};
}


#endif