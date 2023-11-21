@tool
extends Sprite2D
class_name FloorSprite2D


@export var floor_id: int:
	get: return floor_id
	set(i):
		if floor_id == i:
			return
		elif i == SteeleID.NULL_ID:
			texture = null
			return
		
		floor_id = i
		__update()
		
@export var direction: int:
	get:
		return direction
	set(value):
		if direction == value:
			return
		
		direction = value
		__update()

@export var debug: bool = false


var floor: ResourceFloor:
	get: return ResourceFloor.g_get(floor_id)
	set(i):
		floor_id = i.id if i != null else SteeleID.NULL_ID

var texture_resource: ResourceDirectionalTexture:
	set(v):
		if v == null:
			floor_id = SteeleID.NULL_ID
			texture = null
		else:
			direction = v.direction
			floor_id = v.parent_id


func __update():
	if debug && texture != null:
		return
	
	texture = ResourceFloor.g_get_direction_texture(floor_id, direction)
