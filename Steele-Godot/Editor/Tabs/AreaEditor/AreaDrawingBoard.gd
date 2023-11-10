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
		var cell: CellNode = c_map.get_at_v2(event.at)
		cell.ground.ground_id = brush_id
	

func handle_grid_mouse_click(event: GridCellButtonArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		c_map.clear_at_v2(event.at, 0)
		return
	
	if brush_id == null:
		return
	
	if event.button_mask == MOUSE_BUTTON_LEFT:
		var cell: CellNode = c_map.get_at_v2(event.at)
		cell.ground.ground_id = brush_id

