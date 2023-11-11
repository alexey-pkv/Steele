@tool
extends Control
class_name AreaDrawingBoard


var brush_id: ResourceID = null:
	get: return brush_id
	set(b): brush_id = b
	

var c_map: MapPatchNode: 
	get: return $_margin/Control/DrawingBoard/MapPatchNode if is_inside_tree() else null


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


var last_dir = Direction.NORTH

func handle_grid_mouse_motion(event: GridCellMotionArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		c_map.clear_at_v2(event.at, 0)
		return
	
	if brush_id == null:
		return
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		var cell: Cell = Cell.new()
		var tile = GroundTile.new()
		
		tile.direction = last_dir
		tile.tile = brush_id.registry_id
		
		last_dir = Direction.rotate_clockwise(last_dir)
		
		cell.add_ground_tile(tile)
		
		c_map.set_at_v2(event.at, cell)
	

func handle_grid_mouse_click(event: GridCellButtonArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		c_map.clear_at_v2(event.at, 0)
		return
	
	if brush_id == null:
		return
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		var cell: Cell = Cell.new()
		var tile = GroundTile.new()
		
		tile.direction = last_dir
		tile.tile = brush_id.registry_id
		
		last_dir = Direction.rotate_clockwise(last_dir)
		cell.add_ground_tile(tile)
		
		c_map.set_at_v2(event.at, cell)

