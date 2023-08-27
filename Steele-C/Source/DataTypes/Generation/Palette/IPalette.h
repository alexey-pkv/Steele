#ifndef STEELE_IPALETTE_H
#define STEELE_IPALETTE_H


#include <string>


namespace Steele
{
	class IPalette
	{
	public:
		virtual const std::string& Name() const = 0;
	};
}


#endif