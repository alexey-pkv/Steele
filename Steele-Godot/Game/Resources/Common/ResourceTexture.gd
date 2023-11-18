@tool
extends SteeleResource
class_name ResourceTexture


@export var texture: Texture2D


func _init(_type: int = TYPE_UNDEFINED, _texture: Texture2D = null):
	super(_type)
	texture = _texture


func has_texture() -> bool:
	return texture != null
