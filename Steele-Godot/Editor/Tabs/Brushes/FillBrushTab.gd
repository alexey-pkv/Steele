@tool
extends GenericTab


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


func load_resource() -> void:
	pass
