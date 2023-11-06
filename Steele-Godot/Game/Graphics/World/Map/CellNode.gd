@tool
extends Node2D
class_name CellNode


@export var cell_size: Vector3i = Vector3i(32, 16, 0): 
	get: return cell_size
	set(v): 
		cell_size = v
		_update_cell_position()


var floor: GroundSprite2D: 
	get: return $Floor


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []

func _update_cell_position() -> void:
	if is_inside_tree():
		$Floor.position = -Vector2(cell_size.x / 2, cell_size.y / 2)


func _ready():
	_update_cell_position()


