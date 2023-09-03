#ifndef STEELE_PAINTEXCEPTION_H
#define STEELE_PAINTEXCEPTION_H


#include "SteeleException.h"


namespace Steele
{
	class PaintException : public SteeleException
	{
	public:
		PaintException() = default;
		~PaintException() override = default;
		
		explicit PaintException(std::string&& msg);
		explicit PaintException(const std::string& msg);
		explicit PaintException(const char* msg);
	};
}


#endif