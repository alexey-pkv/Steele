@tool
extends Control
class_name DrawingBoard


var m_drag_start 	= Vector2()
var m_is_dragging = false


var c_zoom_factor: ZoomFactor: 
	get: return $ZoomFactor
	

func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


func mouse_events_handler(event: InputEventMouseButton):
	if event.button_index == MOUSE_BUTTON_WHEEL_DOWN:
		if event.pressed:
			c_zoom_factor.zoom_out()
	elif event.button_index == MOUSE_BUTTON_WHEEL_UP:
		if event.pressed:
			c_zoom_factor.zoom_in()
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

