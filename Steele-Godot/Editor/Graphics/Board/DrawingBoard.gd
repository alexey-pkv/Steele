@tool
extends Node2D
class_name DrawingBoard


var m_drag_start 	= Vector2()
var m_is_dragging = false


@export var debug_mod: bool = false:
	get: return debug_mod
	set(v):
		debug_mod = v
		
		if is_inside_tree():
			$Debug_Label.visible = v


@export var mouse_control_node: Control:
	set(n): 
		_disconnect_events()
		mouse_control_node = n
		_connect_events()


var c_zoom_factor: ZoomFactor: 
	get: return $ZoomFactor
	

func _get_configuration_warnings():
	var notes = []
	
	if is_inside_tree() && get_child_count() == 0:
		notes.push_back("Scene incorrectly imported")
	if mouse_control_node == null:
		notes.push_back("Mouse control node must be set")
	
	return notes


func _disconnect_events() -> void:
	if mouse_control_node == null:
		return
	
	mouse_control_node.gui_input.disconnect(_handle_gui_input)
	
func _connect_events() -> void:
	if mouse_control_node == null:
		return
	
	mouse_control_node.gui_input.connect(_handle_gui_input)


func mouse_events_handler(event: InputEventMouseButton):
	if event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
		if event.pressed:
			c_zoom_factor.zoom_out(to_local(event.global_position))
	elif event.button_index == MOUSE_BUTTON_WHEEL_UP:
		if event.pressed:
			c_zoom_factor.zoom_in(to_local(event.global_position))
	elif event.button_index == MOUSE_BUTTON_MIDDLE:
		set_dragging(event)

func set_dragging(event):
	if event.pressed:
		m_is_dragging = true
		m_drag_start = get_global_mouse_position()
	else:
		m_is_dragging = false
		
func drag_camera(event) -> void:
	if !m_is_dragging or !(event is InputEventMouseMotion):
		return
		
	var drag_end = get_global_mouse_position()
	var drag_vector = drag_end - m_drag_start
	
	position += drag_vector
	
	m_drag_start = drag_end


func _reset() -> void:
	position = Vector2.ZERO
	c_zoom_factor.applay_default_zoom()

func _handle_gui_input(event):
	if event is InputEventMouseButton:
		mouse_events_handler(event)
		
		if event.button_index == MOUSE_BUTTON_MIDDLE:
			set_dragging(event)
	
	if m_is_dragging:
		drag_camera(event)
	
	if event is InputEventKey:
		if event.as_text_keycode() == 'R':
			_reset()

func _ready():
	if debug_mod:
		$Debug_Label.visible = debug_mod
