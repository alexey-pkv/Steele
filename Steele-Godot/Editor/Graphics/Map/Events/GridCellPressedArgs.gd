@tool
extends GridCellArgs
class_name GridCellPressedArgs


@export var mouse_motion_event: InputEventMouseMotion = null:
	get: return mouse_motion_event
	set(e): mouse_motion_event = e
	
@export var mouse_button_event: InputEventMouseButton = null:
	get: return mouse_button_event
	set(e): mouse_button_event = e


var mouse_event: InputEventMouse = null:
	get: 
		var m = mouse_motion_event
		
		if m == null:
			m = mouse_button_event
		
		return m.button_mask
	set(e): 
		if e is InputEventMouseMotion:
			mouse_motion_event = e
			mouse_button_event = null
		elif e is InputEventMouseButton:
			mouse_motion_event = null
			mouse_button_event = e
		else:
			mouse_motion_event = null
			mouse_button_event = null

var is_motion_event: bool:
	get: return mouse_motion_event != null

var is_button_event: bool:
	get: return mouse_button_event != null


var button_mask: MouseButtonMask:
	get: return mouse_event.button_mask

