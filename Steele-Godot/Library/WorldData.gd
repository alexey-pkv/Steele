class_name WorldData


@export var direction: int = Direction.NORTH:
	set (value): 
		var original = direction
		direction = value
		on_direction_changed.emit(value, original)
	get:
		return direction


func roate_clockwise() -> void:
	direction = Direction.rotate_clockwise(direction)

func roate_counter_clockwise() -> void:
	direction = Direction.rotate_counter_clockwise(direction)

func get_texture(direction: int, base_id: int) -> TextureData:
	return null

func applay_texture_on_sprite(sprite: Sprite2D, direction: int, base_id: int) -> TextureData:
	var textureData = get_texture(direction, base_id)
	
	if textureData == null:
		sprite.texture = null
	else:
		textureData.applay_on_sprite(sprite)
	
	return textureData


signal on_direction_changed(direction: int, original: int)
