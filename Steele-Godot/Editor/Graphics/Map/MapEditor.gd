extends Control


var c_grid: IsometricGrid: 
	get: return $Board/Grid if is_inside_tree() else null

var z_level: int = 0: 
	get: return z_level
	set(i): z_level = i


var m_event_mouse_mask: int = 0
var m_event_last_cell: Vector3i = Vector3i.ZERO
var m_event_has_last_cell: bool = false


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


func _handle_button_change(event: InputEventMouse) -> void:
	pass


func _handle_mouse_motion(event: InputEventMouseMotion):
	pass

func _handle_mouse_button(event: InputEventMouseButton):
	print(event.button_mask)
	print("Button")


func _handle_board_gui_input(event):
	if !(event is InputEventMouse):
		return
	
	_handle_button_change(event)
	
	if event is InputEventMouseMotion:
		_handle_mouse_motion(event)
	elif event is InputEventMouseButton:
		_handle_mouse_button(event)


signal on_press(args: GridCellClickedArgs)
signal on_click(args: GridCellClickedArgs)
signal on_hover(args: GridCellHoverArgs)
signal on_release(args: GridCellReleasedArgs)

