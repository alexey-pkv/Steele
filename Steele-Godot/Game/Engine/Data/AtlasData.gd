extends AbstractRegistryObject
class_name AtlasData


var rows: int:
	get:		return rows
	set(value): rows = value

var cell_size: Vector2:
	get:		return cell_size
	set(value):	cell_size = value

func get_child_ids() -> Array[ResourceID]:
	var ids = []
	var _id = id
	
	if _id == null:
		return ids
	
	for i in range(0, rows):
		ids.push_back(_id.create_child_i(i))
	
	return ids


static func create_gound_atlas(p_id: ResourceID) -> AtlasData:
	return AtlasData.new(p_id, TemplateType.TYPE_GROUND_ATLAS)
