#ifndef STEELE_ACTOR_H
#define STEELE_ACTOR_H


#include "Element.h"
#include "DataTypes/World/Actor/PersonalName.h"


namespace Steele
{
	struct Actor : public Element
	{
	public:
		PersonalName	Name;
		
		// TODO: Other info?aaa
	};
}


#endif