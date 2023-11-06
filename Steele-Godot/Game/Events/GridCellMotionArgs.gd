@tool
extends GridCellArgs
class_name GridCellMotionArgs


@export var previous_at: Vector2i:
	get: return previous_at
	set(v): previous_at = v

@export var mouse_event: InputEventMouseMotion:
	get: return mouse_event
	set(e): mouse_event = e


var button_mask: MouseButtonMask:
	get: return mouse_event.button_mask
