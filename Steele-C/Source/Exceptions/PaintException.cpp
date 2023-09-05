#include "PaintException.h"


Steele::PaintException::PaintException(std::string&& msg) : SteeleException(msg) {}
Steele::PaintException::PaintException(const std::string& msg) : SteeleException(msg) {}
Steele::PaintException::PaintException(const char* msg) : SteeleException(msg) {}


Steele::NoGroundInPaletteException::NoGroundInPaletteException()
	: PaintException("There are no ground elements inside the referenced palette") {}

Steele::NoPaletteException::NoPaletteException()
	: PaintException("Referenced palette not found") {}
