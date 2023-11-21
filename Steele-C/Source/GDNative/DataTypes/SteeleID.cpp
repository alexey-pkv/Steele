#include "SteeleID.h"


using namespace godot;


int SteeleID::m_last = 0;	


void SteeleID::_bind_methods()
{
	ClassDB::bind_static_method("SteeleID", D_METHOD("next"), &SteeleID::next);
	ClassDB::bind_static_method("SteeleID", D_METHOD("reset"), &SteeleID::reset);
	
	BIND_CONSTANT(MAX_ID)
	BIND_CONSTANT(MIN_ID)
	BIND_CONSTANT(NULL_ID)
}


void SteeleID::reset()
{
	m_last = 0;
}

int SteeleID::next()
{
	if (m_last == MAX_ID)
	{
		m_last = MIN_ID;
	}
	else
	{
		m_last++;
	}
	
	return m_last;
}
