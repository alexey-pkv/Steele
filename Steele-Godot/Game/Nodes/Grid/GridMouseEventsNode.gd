@tool
extends Node


const NULL_HOVER_VECTOR: Vector2i	= Vector2i(9223372036854775807, 9223372036854775807)

var m_is_on_hover:		bool		= false
var m_last_hover_cell:	Vector2i	= Vector2i.ZERO


func _get_configuration_warnings():
	var notes = []
	
	if isometric_grid == null:
		notes.push_back("Isometric grid node not set")
	if mouse_control_node == null:
		notes.push_back("Control node with mouse events not set")
	
	return notes


@export var isometric_grid: IsometricGrid:
	set(n): isometric_grid = n

@export var mouse_control_node: Control:
	set(n): 
		if mouse_control_node != null: 
			_disconnect_events()
		
		mouse_control_node = n
		
		if mouse_control_node != null: 
			_connect_events()


func handle_click(event: InputEventMouseButton):
	var grid_event: GridCellButtonArgs = Isometric.create_grid_event_mouse_button(event, isometric_grid, isometric_grid.size)
	on_click.emit(grid_event)
	
func handle_hover(event: InputEventMouseMotion):
	var last_pos = m_last_hover_cell if m_is_on_hover else NULL_HOVER_VECTOR
		
	var arg_hover = Isometric.create_grid_event_mouse_motion(
		event, isometric_grid, isometric_grid.size, last_pos)
	
	if arg_hover == null:
		return
	
	if !m_is_on_hover:
		arg_hover.previous_at = arg_hover.at
	
	m_is_on_hover = true
	m_last_hover_cell = arg_hover.at
	
	on_hover.emit(arg_hover)


func handle_mouse_exited():
	m_is_on_hover = false 


func handle_gui_event(event: InputEvent):
	if !(event is InputEventMouse):
		return
	
	if event is InputEventMouseButton:
		handle_click(event)
	elif event is InputEventMouseMotion:
		handle_hover(event)


func _disconnect_events() -> void:
	mouse_control_node.gui_input.disconnect(handle_gui_event)
	mouse_control_node.mouse_exited.disconnect(handle_mouse_exited)
	
func _connect_events() -> void:
	mouse_control_node.gui_input.connect(handle_gui_event)
	mouse_control_node.mouse_exited.connect(handle_mouse_exited)


signal on_hover(event: GridCellMotionArgs)
signal on_click(event: GridCellButtonArgs)

