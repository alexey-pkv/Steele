@tool
extends GridCellMouseArgs
class_name GridCellMotionArgs


@export var previous_at: Vector2i
@export var mouse_event: InputEventMouseMotion


func get_mouse_event() -> InputEventMouse:
	return mouse_event

