extends Sprite2D
class_name GroundSprite2D


@export var ground: int:
	get: 
		return ground
	set(value):
		if value == ground:
			return
		
		ground = value
		__update()
		
@export var direction: int:
	get:
		return direction
	set(value):
		if direction == value:
			return
		
		direction = value
		__update()

var ground_id: ResourceID:
	set(value):
		ground = value.registry_id if value != null else 0


func __update():
	var id = ground
	var dir = direction
	
	if id == 0 || !TexturesRegistryNode.has_glboal():
		texture = null
	else:
		dir = WorldDataNode.get_direction(self, dir)
		texture = TexturesRegistryNode.g_get_ground(id, dir)
	
