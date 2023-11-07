@tool
extends GenericTab
class_name AreaEditorTag


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


func load_resource() -> void:
	pass


var c_resources: ResourceExplorer: 
	get: return $_split_container/ResourceExplorer

var c_area: AreaDrawingBoard: 
	get: return $_split_container/AreaDrawingBoard


func _on_resource_explorer_on_selected(id: ResourceID):
	c_area.brush_id = id
