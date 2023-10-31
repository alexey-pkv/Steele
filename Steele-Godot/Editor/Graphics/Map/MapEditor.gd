@tool
extends Control
class_name MapEditor


var c_grid: IsometricGrid: 
	get: return $Board/Grid if is_inside_tree() else null

var z_level: int = 0: 
	get: return z_level
	set(i): z_level = i


var m_event_mouse_mask: int = 0
var m_event_last_cell: Vector3i = Vector3i.ZERO
var m_event_has_last_cell: bool = false


func _get_configuration_warnings():
	if is_inside_tree() && get_child_count() == 0:
		return ["Node " + name + " should be initialized as scene!"]
	
	return []



func _is_hovered_cell_changed(curr: Vector3i) -> bool:
	if !m_event_has_last_cell:
		return true
	else:
		return curr != m_event_last_cell

func _get_last_cell(curr: Vector3i) -> Vector3i:
	var last = m_event_last_cell
	
	m_event_last_cell = curr
	
	if !m_event_has_last_cell:
		last					= curr
		m_event_has_last_cell	= true
	
	return last


func _get_cell_at_mouse(event: InputEventMouse) -> Vector3i:
	var grid = c_grid
	
	if grid == null:
		return Vector3i.ZERO
	
	var at = grid.global_to_grid(event.position)
	
	return Vector3i(at.x, at.y, z_level)


func _handle_mouse_motion(event: InputEventMouseMotion):
	var grid: IsometricGrid = c_grid
	var at: Vector3i = _get_cell_at_mouse(event)
	
	if grid == null || !_is_hovered_cell_changed(at):
		return
	
	var args = GridCellHoverArgs.new()
	
	args.mouse_event	= event
	args.at_v3			= at
	args.previous_v3	= _get_last_cell(at)
	
	on_hover.emit(args)
	

func _handle_mouse_button(event: InputEventMouseButton):
	var grid: IsometricGrid = c_grid
	var at: Vector3i = _get_cell_at_mouse(event)
	
	if grid == null:
		return
	
	var args = GridCellButtonArgs.new()
	
	args.mouse_event	= event
	args.at_v3			= at
	
	on_mouse_button.emit(args)


func _handle_board_gui_input(event):
	if !(event is InputEventMouse):
		return
	
	if event is InputEventMouseMotion:
		_handle_mouse_motion(event)
	elif event is InputEventMouseButton:
		_handle_mouse_button(event)


signal on_mouse_button(args: GridCellButtonArgs)
signal on_hover(args: GridCellHoverArgs)

