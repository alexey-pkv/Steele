extends Sprite2D
class_name WallSprite2D


const LEFT: 	int	= 0
const RIGHT:	int	= 1


var wall_texture: WallTexture:
	set (value):
		wall_texture = value
		update_sprite()
	get:
		return wall_texture

var wall_side: int = LEFT:
	set (value):
		var a =Vector2i(1, 2)
		
		wall_side = value
		update_sprite()
	get:
		return wall_side


func update_sprite():
	if wall_texture == null:
		return
	
	if wall_side == LEFT:
		wall_texture.aplay_left_texture(self)
	else:
		wall_texture.aplay_right_texture(self)
