#ifndef STEELE_BLOCKTYPECONFIG_H
#define STEELE_BLOCKTYPECONFIG_H


#include "DataTypes/Types.h"


namespace Steele
{
	struct BlockTypeConfig
	{
	public:
		int m_generated = 0;
		
		
	public:
		v2i Size = {};
		int Min = 0;
		int Max = 0;
		int Weight = 0;
		
		
	public:
		inline int get_generated() const { return m_generated; }
		inline void add_generated() { m_generated++; }
		inline bool is_at_max() const { return Max >= 0 && m_generated >= Max; }
	};
}


#endif