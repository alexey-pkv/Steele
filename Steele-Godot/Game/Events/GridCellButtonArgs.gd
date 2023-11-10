@tool
extends GridCellArgs
class_name GridCellButtonArgs


@export var mouse_event: InputEventMouseButton:
	get: return mouse_event
	set(e): mouse_event = e


var button_mask: int:
	get: return mouse_event.button_mask
