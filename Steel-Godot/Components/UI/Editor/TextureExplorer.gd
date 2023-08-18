extends Control
class_name TextureExplorer


var __selected: Cell2D = null


var __cells_container: HFlowContainer:
	get:
		return $ScrollContainer/HFlowContainer


var selected: Cell2D:
	get:
		return __selected


func _ready():
	pass


func select_at(at: int) -> void:
	pass

func select_by_name(name: String) -> void:
	pass

func add_ground_texture(ground_texture: GroundTexture, scale_factor: float) -> void:
	var cell_container = Cell2DContainer.create_for_ground_texture(
		ground_texture, 
		Direction.NORTH,
		scale_factor
	)
	
	__cells_container.add_child(cell_container)

func add_ground_textures(ground_textures: GroundTextures, scale_factor: float = 1) -> void:
	for ground_texture in ground_textures.get_textures():
		add_ground_texture(ground_texture, scale_factor)


signal on_selected(cell: Cell2D)
signal on_ground_selected(ground_texture: GroundTexture, direction: int)
