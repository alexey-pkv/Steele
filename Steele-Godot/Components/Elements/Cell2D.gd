extends Node2D
class_name Cell2D


var __ground: GroundSprite2D:
	get:
		return $GroundSprite2D


var ground_texture: GroundTexture = null:
	set (value):
		if __ground.ground_texture == value:
			return
		
		__ground.ground_texture = value
	get:
		return __ground.ground_texture

var ground_direction: int = Direction.NORTH:
	set(value):
		if __ground.direction == value:
			return
		
		__ground.direction = value
	get:
		return __ground.direction


func get_texture_size() -> Vector2:
	return __ground.get_texture_size()

func get_area_size() -> Vector2:
	var size = __ground.get_texture_size()
	
	size.x = size.x * scale.x
	size.y = size.y * scale.y
	
	return size

func is_empty() -> bool:
	return __ground.ground_texture.has_any_textures()
