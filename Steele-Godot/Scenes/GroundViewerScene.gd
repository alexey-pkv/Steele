extends Control


@export var m_textures: GroundTextures = null


@onready var ground_view = $GroundView


var world_data: WorldData = WorldData.new()
var current_index: int = 0


func __set_texture() -> void:
	var texture = m_textures.get_texture_at(current_index)
	
	if texture != null:
		ground_view.ground_texture = texture
	

func __next_texture() -> void:
	current_index = current_index + 1
	
	if current_index >= m_textures.count():
		current_index = 0
	
	__set_texture()


func __prev_texture() -> void:
	current_index = current_index - 1
	
	if current_index < 0:
		current_index = m_textures.count() - 1
	
	__set_texture()


func __rotate_clockwise() -> void:
	world_data.roate_clockwise()

func __rotate_counter_clockwise() -> void:
	world_data.roate_counter_clockwise()


func _ready():
	m_textures = SceneParams.get_params()
	
	ground_view.world_data = world_data
	
	__set_texture()


func _input(e):
	if e is InputEventKey && e.pressed:
		if e.keycode == KEY_LEFT: 
			__prev_texture()
		elif e.keycode == KEY_RIGHT: 
			__prev_texture()
		elif e.keycode == KEY_Z: 
			__rotate_counter_clockwise()
		elif e.keycode == KEY_X: 
			__rotate_clockwise()

