extends Control


@export var cell_size: Vector3i = Vector3i(32, 16, 0): 
	get: return cell_size
	set(v): 
		cell_size = v
		
		if is_inside_tree():
			c_map.cell_size	= v
			c_hover.size	= v


var c_map: MapPatchNode: 
	get: return $DrawingBoard/MapPatchNode if is_inside_tree() else null
	
var c_hover: IsometricGrid:
	get: return $DrawingBoard/Grid if is_inside_tree() else null


func set_hover(at: Vector3i, n: Node2D) -> void:
	c_hover.clear()
	c_hover.set_at_v3i(at, n)

func get_map() -> MapPatchNode:
	return c_map 


func handle_grid_mouse_motion(event: GridCellMotionArgs):
	var points = []
	
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		var line = Vectors.get_line(event.previous_at, event.at)
		
		for v in line:
			points.push_back(Vector3i(v.x, v.y, 0))
			c_map.clear_at_v2(v, 0)
		
		on_remove_at.emit(points)
	
	elif event.button_mask == MOUSE_BUTTON_LEFT:
		var line = Vectors.get_line(event.previous_at, event.at)
		
		for v in line:
			points.push_back(Vector3i(v.x, v.y, 0))
		
		on_place_at.emit(points)
	
	on_hover.emit(event)

func handle_grid_mouse_click(event: GridCellButtonArgs):
	if event.button_mask == MOUSE_BUTTON_RIGHT:
		
		c_map.clear_at_v2(event.at, 0)
		on_remove_at.emit([Vector3i(event.at.x, event.at.y, 0)])
		
	elif event.button_mask == MOUSE_BUTTON_LEFT:
		
		on_place_at.emit([Vector3i(event.at.x, event.at.y, 0)])


func _ready():
	c_map.cell_size	= cell_size
	c_hover.size	= cell_size


signal on_hover(event: GridCellMotionArgs)
signal on_remove_at(at: Array[Vector3i])
signal on_place_at(at: Array[Vector3i])
