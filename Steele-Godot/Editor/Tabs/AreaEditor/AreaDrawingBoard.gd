@tool
extends Control
class_name AreaDrawingBoard


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []
