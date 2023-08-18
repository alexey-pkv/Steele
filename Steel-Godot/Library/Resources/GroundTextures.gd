extends Resource
class_name GroundTextures


@export var m_textures: Dictionary	= {}


func count() -> int:
	return len(m_textures)

func get_texture_at(at: int) -> GroundTexture:
	var all = get_textures()
	
	if at >= 0 && at < len(all):
		return all[at]
	
	return null

func get_textures() -> Array:
	return m_textures.values()

func add_texture(textures: GroundTexture) -> void:
	m_textures[textures.name] = textures

func get_texture(name: String) -> GroundTexture:
	if name in m_textures:
		return m_textures[name]
	
	return null

func has_texture(name: String) -> bool:
	return name in m_textures

func get_names() -> Array[String]:
	return m_textures.keys()
