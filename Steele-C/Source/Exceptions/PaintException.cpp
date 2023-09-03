#include "PaintException.h"


Steele::PaintException::PaintException(std::string&& msg) : SteeleException(msg)
{
	
}

Steele::PaintException::PaintException(const std::string& msg) : SteeleException(msg)
{
	
}

Steele::PaintException::PaintException(const char* msg) : SteeleException(msg)
{
	
}
