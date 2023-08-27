#ifndef STEELE_MAPEXCEPTIONS_H
#define STEELE_MAPEXCEPTIONS_H


#include "SteeleException.h"

namespace Steele
{
	class NotInTransactionException : public SteeleException
	{
	public:
		NotInTransactionException();
		~NotInTransactionException() override = default;
	};
	
	class NoTransformationException : public SteeleException
	{
	public:
		NoTransformationException();
		~NoTransformationException() override = default;
	};
}



#endif