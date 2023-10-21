extends Node2D
class_name GroundTextureView


static func inst() -> GroundTextureView:
	var i = load("res://Editor/Graphics/Textures/Ground/GroundTextureView.tscn")
	return i.instantiate()


@export var cell_size: Vector2:
	get: return cell_size
	set(value):
		if cell_size == value: 
			return
		
		cell_size = value
		_redraw()
		
@export var padding: float:
	get: return padding
	set(value):
		if padding == value: 
			return
		
		padding = value
		_redraw()


var size: Vector2:
	get: return Vector2(
		cell_size.x * 4 + padding * 3,
		cell_size.y
	)

var ground_id: ResourceID:
	get: return ground_id
	set(value):
		ground_id = value
		_redraw()


func _sprites() -> Array[GroundSprite2D]:
	if !is_inside_tree():
		return []
	
	return [
		$Ground_North,
		$Ground_East,
		$Ground_South,
		$Ground_West
	]


func _redraw() -> void:
	if !is_inside_tree():
		return
	
	var sprites = _sprites()
	
	if len(sprites) == 0:
		return
	
	var offset = cell_size.x + padding
	var pos = cell_size / 2
	var dir = Direction.NORTH
	
	for i in range(4):
		var sprite = sprites[i]
		
		if sprite == null:
			continue
		
		if ground_id == null:
			sprite.ground_id = null
		else:
			sprite.ground_id	= ground_id
			sprite.direction	= dir
			sprite.position		= pos
		
		dir = Direction.rotate_clockwise(dir)
		pos.x += offset
	
	queue_redraw()

func _enter_tree():
	_redraw()
