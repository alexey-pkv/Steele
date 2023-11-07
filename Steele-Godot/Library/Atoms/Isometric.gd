class_name Isometric


const STYLE_CENTER		= 0
const STYLE_TOP_LEFT	= 1


static func grid_to_local(v_grid: Vector3i, grid_size: Vector3i, style: int = STYLE_CENTER) -> Vector2i:
	grid_size = grid_size / 2
	
	var v = Vector2i(
		v_grid.x * grid_size.x + v_grid.y * grid_size.x,
		v_grid.x * grid_size.y - v_grid.y * grid_size.y - v_grid.z * grid_size.z
	);
	
	if (style != STYLE_CENTER):
		v += Vector2i(grid_size.x, grid_size.y)
	
	return v

static func local_to_grid(v_at: Vector2, grid_size: Vector3i, style: int = STYLE_CENTER) -> Vector2i:
	grid_size = grid_size / 2
	
	if (style != STYLE_CENTER):
		v_at -= Vector2(grid_size.x, grid_size.y)
	
	var n: Vector2 = Vector2(
		v_at.x / float(grid_size.x),
		v_at.y / float(grid_size.y)
	)
	
	return Vector2(
		round((n.x + n.y) / 2),
		round((n.x - n.y) / 2),
	)


static func mouse_to_grid(
		mouse_at: Vector2i, 
		grid:		Node2D, 
		cell_size:	Vector3i) -> Vector2i:
	
	return local_to_grid(grid.to_local(mouse_at), cell_size)
	

static func create_grid_event_mouse_motion(
		event:		InputEventMouseMotion, 
		grid:		Node2D, 
		cell_size:	Vector3i,
		last_cell:	Vector2i) -> GridCellMotionArgs:
	
	if grid == null: return null
	
	var at_grid: Vector2i = mouse_to_grid(event.global_position, grid, cell_size)
	
	if at_grid == last_cell:
		return null
	
	var args = GridCellMotionArgs.new()
	
	args.mouse_event	= event
	args.at				= at_grid
	args.previous_at	= last_cell
	
	return args
	
static func create_grid_event_mouse_button(
		event:		InputEventMouseButton, 
		grid:		Node2D, 
		cell_size:	Vector3i) -> GridCellButtonArgs:
	
	if grid == null: return null
	
	var args = GridCellButtonArgs.new()
	
	args.mouse_event	= event
	args.at				= mouse_to_grid(event.global_position, grid, cell_size)
	
	return args








