#ifndef STEELE_PAINTEXCEPTION_H
#define STEELE_PAINTEXCEPTION_H


#include "SteeleException.h"
#include "DataTypes/Types.h"


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
		
		
	public:
		template<class ... T >
		explicit PaintException(T&& ... args) : SteeleException(std::forward<T>(args)...) {}
		
		template<class ... T >
		explicit PaintException(const T& ... args) : SteeleException(std::forward<const T>(args)...) {}
	};
	
	
	class NoGroundInPaletteException : public PaintException
	{
	public:
		~NoGroundInPaletteException() override = default;
		NoGroundInPaletteException();
	};
	
	class DrawingAreaDoesNotOverlapException : public PaintException
	{
	public:
		~DrawingAreaDoesNotOverlapException() override = default;
		DrawingAreaDoesNotOverlapException();
	};
	
	class NoPaletteException : public PaintException
	{
	public:
		~NoPaletteException() override = default;
		NoPaletteException();
	};
	
	
	class MisconfiguredBrushException : public PaintException
	{
	public:
		~MisconfiguredBrushException() override = default;
		MisconfiguredBrushException() = delete;
		
	public:
		template<class ... T >
		explicit MisconfiguredBrushException(T&& ... args) : PaintException(std::forward<T>(args)...) {}
	};
	
	class CanvasAreaOutsideOfBoundException : public PaintException
	{
	public:
		~CanvasAreaOutsideOfBoundException() override = default;
		CanvasAreaOutsideOfBoundException(v2i position);
	};
	
	class AbortException : public PaintException
	{
	public:
		~AbortException() override = default;
		AbortException();
	};
}


#endif