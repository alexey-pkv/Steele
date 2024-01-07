#ifndef STEELE_CHAOSMANAGER_H
#define STEELE_CHAOSMANAGER_H


#include "DataTypes/RNG/RandomState.h"


namespace Steele
{
	class ChaosManager
	{
	public:
		RandomState		Primary;
		
		RandomState		MapGeneration;
		RandomState		Naming;
		RandomState		Quests;
		
		
	public:
		void init(const std::string& seed);
	};
}


#endif