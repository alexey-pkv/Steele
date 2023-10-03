#ifndef STEELE_JSONEXCEPTION_H
#define STEELE_JSONEXCEPTION_H


#include "SteeleException.h"


namespace Steele
{
	class JSONException : public SteeleException
	{
	public:
		JSONException() = default;
		~JSONException() override = default;
		
		
	public:
		template<class ... T >
		explicit JSONException(T&& ... args) : SteeleException(std::forward<T>(args)...) {}
		
		template<class ... T >
		explicit JSONException(const T& ... args) : SteeleException(std::forward<const T>(args)...) {}
	};
}


#endif