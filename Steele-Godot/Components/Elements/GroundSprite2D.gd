extends Sprite2D
class_name GroundSprite2D


@export var direction: int = Direction.NORTH:
	set (value):
		direction = value
		update_texture()
	get:
		return direction
	
@export var ground_texture: GroundTexture = null:
	set (value):
		ground_texture = value
		update_texture()
	get:
		return ground_texture


func update_texture() -> void:
	if ground_texture == null:
		texture = null
		return
	
	var data = ground_texture.get_texture_data(direction)
	
	if data == null:
		texture = null
	else:
		data.aplay_on_sprite(self)

func get_texture_size() -> Vector2:
	if ground_texture == null:
		return Vector2.ZERO
	
	return ground_texture.get_size()
