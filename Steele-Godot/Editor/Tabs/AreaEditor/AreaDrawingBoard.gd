@tool
extends Control
class_name AreaDrawingBoard


const SCENE_CellNode = preload("res://Game/Graphics/World/Map/CellNode.tscn")


var brush_id: ResourceID = null:
	get: return brush_id
	set(b): brush_id = b
	

var c_map: MapPatchNode: 
	get: return $_margin/Control/DrawingBoard/MapPatchNode if is_inside_tree() else null
	
var c_hover: IsometricGrid:
	get: return $_margin/Control/DrawingBoard/HoverGrid if is_inside_tree() else null


var current_hover_x = null
var current_hover_y = null

	
func draw_placeholder(event: GridCellMotionArgs):
	if brush_id == null:
		return
	
	if (current_hover_x == event.at.x && current_hover_y == event.at.y):
		return
		
	var cell = SCENE_CellNode.instantiate()
	
	if (current_hover_x != null && current_hover_y != null):
		c_hover.remove(current_hover_x, current_hover_y, 0)
	
	current_hover_x = event.at.x
	current_hover_y = event.at.y
	
	cell.ground.ground = brush_id.registry_id;
	
	c_hover.set_at(current_hover_x, current_hover_y, 0, cell)

func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


var last_dir = Direction.NORTH

func handle_grid_mouse_motion(event: GridCellMotionArgs):
	draw_placeholder(event);
		
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		var line = Vectors.get_line(event.previous_at, event.at)
		
		for v in line:
			c_map.clear_at_v2(v, 0)
			
		return
	
	if brush_id == null:
		return
		
	draw_placeholder(event);
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		var line = Vectors.get_line(event.previous_at, event.at)
		
		var cell: Cell = Cell.new()
		var tile = GroundTile.new()
		
		tile.direction = last_dir
		tile.tile = brush_id.registry_id
		
		last_dir = Direction.rotate_clockwise(last_dir)
		
		cell.add_ground_tile(tile)
		
		for v in line:
			c_map.set_at_v2(v, cell)
	

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

