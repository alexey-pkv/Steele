@tool
extends Control
class_name PaletteNode


var c_records_list: RecordsList:
	get: return $cont/RecordsList if is_inside_tree() else null


func add_resource(id: ResourceID, weight: int) -> void:
	c_records_list.add_resource(id, weight)

func toggle_resource(id: ResourceID) -> void:
	c_records_list.toggle_resource(id)


func handle_resource_selected(id):
	toggle_resource(id)
