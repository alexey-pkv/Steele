class_name MapChunk


var coordinates: Rect2i
var cells: Dictionary


var top_left_corner: Vector2i:
	get:
		return coordinates.position

var top_right_corner: Vector2i:
	get:
		return coordinates.position + Vector2i(coordinates.size.x, 0)
		
var bottom_left_corner: Vector2i:
	get:
		return coordinates.position + Vector2i(0, coordinates.size.y)

var bottom_right_corner: Vector2i:
	get:
		return coordinates.position + coordinates.size

var area: int:
	get:
		return coordinates.get_area()

var width: int:
	get: 
		return coordinates.size.x
		
var height: int:
	get: 
		return coordinates.size.y


func _init(_coordniates: Rect2i):
	coordinates = _coordniates
	cells = {}
	
	for x in range(0, coordinates.size.x):
		for y in range(0, coordinates.size.y):
			cells[Vector2i(x, y)] = Cell.new()


func get_cell_local(at: Vector2i) -> Cell:
	if at not in cells:
		return null
	
	return cells[at]

func get_cell_global(at: Vector2i) -> Cell:
	return get_cell_local(at - coordinates.position)
