#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"


#ifndef GODOT_STEELE_ID_H
#define GODOT_STEELE_ID_H


#include <godot.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "DataTypes/Types.h"


namespace godot
{
	class SteeleID : public Object
	{
		GDCLASS(SteeleID, Object)
	private:
		static int m_last;
		
	
	public:
    	static void _bind_methods();
	
		
	public:
		static void reset();
		static int next();
		
	
	public:
		static const int NULL_ID	= STEELE_NULL_ID;
		static const int MIN_ID		= 1;
		static const int MAX_ID		= 2147483647;
	};
}


#endif

#pragma clang diagnostic pop