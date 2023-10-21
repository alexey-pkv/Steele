extends RefCounted
class_name TextureRef


const TYPE_TEXTURE	= 0
const TYPE_GROUND	= 1


var m_type: int	= TYPE_TEXTURE
var m_value


var type: int:
	get:
		return m_type


static func _create_repeating_ref(source: Texture2D, p_type: int, repeats: int, row: int, size: Vector2) -> TextureRef:
	var textures = []
	var region = Rect2(Vector2(0, size.y * row), size)
	var step = size.x
	
	for i in range(0, repeats):
		var dir_texture = AtlasTexture.new()
		
		dir_texture.atlas = source
		dir_texture.region = region
		
		textures.push_back(dir_texture)
		
		region.position.x += step
	
	return TextureRef.new(p_type, textures)


func _init(ref_type: int, value):
	m_type = ref_type
	m_value = value


func get_texture(i = null) -> Texture2D:
	if m_type == TYPE_TEXTURE:
		return m_value
	elif m_type == TYPE_GROUND:
		i = Direction.dir_floor(i)
		i = i / 2
		return m_value[i]
	else:
		return null

func get_texture_for_type(for_type: int, i = null) -> Texture2D:
	if for_type != m_type:
		return null
	
	return get_texture(i)

static func create_ground_ref(source: Texture2D, row: int, size: Vector2) -> TextureRef:
	return _create_repeating_ref(source, TYPE_GROUND, 4, row, size)

