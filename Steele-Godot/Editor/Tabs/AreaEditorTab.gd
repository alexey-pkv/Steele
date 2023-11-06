@tool
extends GenericTab


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


var c_resources: ResourceExplorer: 
	get: return $_split_container/ResourceExplorer

var c_area: AreaDrawingBoard: 
	get: return $_split_container/AreaDrawingBoard




