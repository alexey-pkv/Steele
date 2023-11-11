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


func handle_grid_mouse_motion(event: GridCellMotionArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		c_map.clear_at_v2(event.at, 0)
		return
	
	if brush_id == null:
		return
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		c_map.create_at_v3(Vector3i(event.at.x, event.at.y, 0))
		
		var cell: Cell = c_map.get_at_v2(event.at)
		cell.get_ground().set(brush_id.registry_id, Direction.NORTH, 0)
		
		c_map.update_at(Vector3i(event.at.x, event.at.y, 0))
	

func handle_grid_mouse_click(event: GridCellButtonArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		c_map.clear_at_v2(event.at, 0)
		return
	
	if brush_id == null:
		return
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		c_map.create_at_v3(Vector3i(event.at.x, event.at.y, 0))
		
		var cell: Cell = c_map.get_at_v2(event.at)		
		var tile = GroundTile.new()
		
		tile.direction = Direction.NORTH
		tile.tile = brush_id.registry_id
		
		cell.add_ground_tile(tile)
		
		c_map.update_at(Vector3i(event.at.x, event.at.y, 0))

