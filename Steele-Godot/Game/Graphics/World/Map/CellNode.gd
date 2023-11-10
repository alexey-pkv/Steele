@tool
extends Node2D
class_name CellNode


var ground: GroundSprite2D: 
	get: return $Floor


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


