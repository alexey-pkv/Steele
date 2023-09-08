#include "PaintException.h"


Steele::PaintException::PaintException(std::string&& msg) : SteeleException(msg) {}
Steele::PaintException::PaintException(const std::string& msg) : SteeleException(msg) {}
Steele::PaintException::PaintException(const char* msg) : SteeleException(msg) {}


Steele::NoGroundInPaletteException::NoGroundInPaletteException()
	: PaintException("There are no ground elements inside the referenced palette") {}

Steele::NoPaletteException::NoPaletteException()
	: PaintException("Referenced palette not found") {}

Steele::CanvasAreaOutsideOfBoundException::CanvasAreaOutsideOfBoundException(v2i position)
	: PaintException("The cell at (", position.x, ": ", position.y, ") is outside of the area bounds")
{
	
}

Steele::DrawingAreaDoesNotOverlapException::DrawingAreaDoesNotOverlapException()
	: PaintException("The drawing area of the brush and target area, do not overlap")
{
	
}
