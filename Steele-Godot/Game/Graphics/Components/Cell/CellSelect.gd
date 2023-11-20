@tool
extends Node2D
class_name CellSelect


func _get_configuration_warnings():
	if is_inside_tree() && get_child_count() == 0:
		return ["Scene incorrectly imported"]
	
	return 

var c_border: Line2D:
	get: return $line if is_inside_tree() else null

var c_fill: Polygon2D:
	get: return $fill if is_inside_tree() else null


@export var cell_size: Vector2: 
	get: return cell_size
	set(v):
		if cell_size == v:
			return
		
		cell_size = v
		_update()

@export var border_color: Color:
	get: return $border.default_color if is_inside_tree() else Color.BLACK
	set(c): if is_inside_tree(): $border.default_color = c

@export var fill_color: Color:
	get: return $fill.color if is_inside_tree() else Color.BLACK
	set(c): if is_inside_tree():  $fill.color = c

@export var border_width: float:
	get: return ($border.width / 2) if is_inside_tree() else -1
	set(w): if is_inside_tree(): $border.width = w * 2


func _update_color() -> void:
	if !is_inside_tree():
		return
	
func _update() -> void:
	if !is_inside_tree():
		return
	
	var half = cell_size / 2
	var dots = [
		Vector2(0,			-half.y),
		Vector2(half.x,		0),
		Vector2(0,			half.y),
		Vector2(-half.x,	0),
		Vector2(0,			-half.y),
	]
	
	$fill.polygon = dots
	$border.points = dots


func _ready():
	_update()

