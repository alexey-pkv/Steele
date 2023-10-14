#ifndef STEELE_JSON_BRUSH_H
#define STEELE_JSON_BRUSH_H


#include "Base/Generation/IBrush.h"
#include "Base/Generation/DB/IBrushDB.h"


namespace Steele
{
	void brush_json_write(json& json, const IBrush& brush);
	void brush_json_read(json& json, IBrushDB& db, t_id id);
	
	
}


#endif