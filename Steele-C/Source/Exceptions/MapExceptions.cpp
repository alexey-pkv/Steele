#include "MapExceptions.h"


Steele::NotInTransactionException::NotInTransactionException()
	: SteeleException("Not in transaction")
{
}

Steele::NoTransformationException::NoTransformationException()
	: SteeleException("No transformation")
{
}