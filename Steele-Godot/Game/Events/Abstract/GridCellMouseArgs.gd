@tool
extends Resource
class_name GridCellMouseArgs


@export var at: Vector2i:
	get: return at
	set(v): at = v


var button_mask: int:
	get: return get_mouse_event().button_mask


func get_mouse_event() -> InputEventMouse:
	push_error("Not Implemented")
	return null
