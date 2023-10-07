#include "json_brush.h"
#include "Exceptions/JSONException.h"


using namespace Steele;


void Steele::brush_json_write(json& json, const IBrush& brush)
{
	json = {
		{ "type",	brush.get_brush_type() },
		{ "brush",	brush }
	};
}

void Steele::brush_json_read(json& json, IBrushDB& db, t_id id)
{
	BrushType type;
	
	if (!json.is_object() || !json.contains("type") || !json["type"].is_string())
		throw JSONException("Invalid JSON format when reading brush");
	if (!json.contains("brush"))
		throw JSONException("Invalid JSON format. Missing brush config");
	
	db.create_from_json(
		id,
		json["type"].get<BrushType>(),
		json["brush"]);
}
