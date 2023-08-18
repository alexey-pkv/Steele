extends Resource
class_name TextureData


@export var texture: Texture2D	= null
@export var flip_h: bool		= false
@export var flip_v: bool		= false


func _init(_texture: Texture2D = null):
	texture = _texture


func aplay_on_sprite(sprite: Sprite2D) -> void:
	if texture == null:
		sprite.texture = null
		return
	
	sprite.texture = texture
	sprite.flip_h = flip_h
	sprite.flip_v = flip_v

func get_size() -> Vector2:
	return texture.get_size()
