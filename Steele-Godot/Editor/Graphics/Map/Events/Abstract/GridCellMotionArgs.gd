@tool
extends GridCellArgs
class_name GridCellMotionArgs


@export var mouse_event: InputEventMouseMotion:
	get: return mouse_event
	set(e): mouse_event = e


var button_mask: MouseButtonMask:
	get: return mouse_event.button_mask
