class_name CellData


var ground_id			:= -1
var ground_direction	:= Direction.NORTH
var walls				:= [-1, -1, -1, -1]


func get_wall(direction: int) -> int:
	return walls[direction / 2]

func set_wall(direction: int, id: int) -> void:
	walls[direction / 2] = id

