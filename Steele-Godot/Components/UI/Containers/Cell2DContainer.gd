extends Container
class_name Cell2DContainer


const self_resource = preload("res://Components/UI/Containers/Cell2DContainer.tscn")


var cell: Cell2D:
	get:
		return $Cell2Dcreate_for_ground_texture

var ground_direction: int = Direction.NORTH:
	set(value):
		cell.ground_direction = value
		__update_size()
	get:
		return cell.ground_direction


func __update_size():
	if !is_inside_tree():
		return
	
	var cell_size = cell.get_area_size()
	
	size = cell_size
	set_custom_minimum_size(size)
	
	cell.position = cell_size / 2


func _ready():
	__update_size()


func set_ground_texture(ground_texture: GroundTexture) -> void:
	cell.ground_texture = ground_texture
	__update_size()

func scale_by(by: float) -> void:
	cell.scale = Vector2(by, by)
	__update_size()


static func create_for_ground_texture(
		ground_texture: GroundTexture, 
		dir: int = Direction.NORTH,
		scale_factor: float = 1) -> Cell2DContainer:
	
	var container = self_resource.instantiate()
	
	container.set_ground_texture(ground_texture)
	container.ground_direction = dir
	container.scale_by(scale_factor)
	
	return container
