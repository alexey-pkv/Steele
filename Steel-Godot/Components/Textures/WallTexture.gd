extends TextureReference
class_name WallTexture


var left: TextureData	= null
var right: TextureData	= null


func aplay_left_texture(sprite: Sprite2D) -> void:
	if left == null:
		sprite.texture = null
	else:
		left.aplay_on_sprite(sprite)

func aplay_right_texture(sprite: Sprite2D) -> void:
	if right == null:
		sprite.texture = null
	else:
		right.aplay_on_sprite(sprite)

func get_size() -> Vector2:
	if right != null:
		return right.get_size()
	elif left != null:
		return left.get_size()
	
	return Vector2(0, 0)
