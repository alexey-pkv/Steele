extends TextureReference
class_name GroundTexture


@export var m_textures: Array[TextureData] = [null, null, null, null]


func get_texture_data(direction: int) -> TextureData: 
	var index = direction / 2
	return m_textures[index]

func set_texture_data(direction: int, data: TextureData) -> void:
	var index = direction / 2
	m_textures[index] = data

func set_texture(direction: int, data: Texture2D) -> void:
	var index = direction / 2
	m_textures[index] = TextureData.new(data)


func get_size() -> Vector2:
	for t in m_textures:
		if t != null:
			return t.get_size()
	
	return Vector2(0, 0)

func has_any_textures() -> bool:
	for t in m_textures:
		if t != null:
			return true
	
	return false

static func create_from_textures(
	name:	String,
	north:	Texture2D, 
	east:	Texture2D, 
	south:	Texture2D, 
	west:	Texture2D) -> GroundTexture:
	
	var ground_texture = GroundTexture.new(name)
	
	ground_texture.set_texture(Direction.NORTH,	north)
	ground_texture.set_texture(Direction.EAST,	east)
	ground_texture.set_texture(Direction.SOUTH,	south)
	ground_texture.set_texture(Direction.WEST,	west)
	
	return ground_texture
	
	
	
	
	
	
	
	
