@tool
extends ResourceTexture
class_name ResourceDirectionalTexture


@export var direction: int


func _init(_type: int, _direction: int, _texture: Texture2D = null): 
	super(_type, _texture)


static func new_floor_texture(_direction: int, _texture: Texture = null) -> ResourceDirectionalTexture:
	return ResourceDirectionalTexture.new(
		SteeleResource.TYPE_FLOOR_TEXTURE, 
		_direction, 
		_texture)
