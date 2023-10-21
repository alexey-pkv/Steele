class_name Isometric


const STYLE_CENTER		= 0
const STYLE_TOP_LEFT	= 1


static func grid_to_local(v_grid: Vector3i, grid_size: Vector3i, style: int = STYLE_CENTER) -> Vector2i:
	grid_size = grid_size / 2
	
	var v = Vector2i(
		v_grid.x * grid_size.x + v_grid.y * grid_size.x,
		v_grid.x * grid_size.y - v_grid.y * grid_size.y - v_grid.z * grid_size.z
	);
	
	if (style == STYLE_CENTER):
		v -= Vector2i(grid_size.x, grid_size.y)
	
	return v
