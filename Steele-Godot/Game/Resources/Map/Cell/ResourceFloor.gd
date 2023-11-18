@tool
extends SteeleResource
class_name ResourceFloor


var m_textures = [SteeleID.NULL, SteeleID.NULL, SteeleID.NULL, SteeleID.NULL]


func _init():
	super(TYPE_FLOOR)
	is_valid = false


func create_direction(dir: int) -> ResourceDirectionalTexture:
	var texture_resource = ResourceDirectionalTexture.new_floor_texture(dir)
	
	setup_child(texture_resource, Direction.get_direction_name(dir))
	
	if !Resources.add_r(texture_resource):
		return null
	
	m_textures[dir_to_index(dir)] = texture_resource.id
	
	return texture_resource
	
func create_directions() -> void:
	create_direction(Direction.NORTH)
	create_direction(Direction.EAST)
	create_direction(Direction.SOUTH)
	create_direction(Direction.WEST)
	is_valid = true
	
func dir_to_index(dir: int) -> int:
	return int(floor(Direction.dir_floor(dir)) / 2)

func has_direction(dir: int) -> int:
	return m_textures[dir_to_index(dir)] != SteeleID.NULL

func get_direction_id(dir: int) -> int:
	return m_textures[dir_to_index(dir)]

func get_direction(dir: int) -> ResourceDirectionalTexture:
	return Resources.get_id(m_textures[dir_to_index(dir)])

func get_directions() -> Array:
	var res = []
	
	for i in len(m_textures):
		res.push_back(get_direction(i * 2))
	
	return res

func get_direction_texture(dir: int) -> Texture2D:
	return Resources.get_texture(m_textures[dir_to_index(dir)])


static func g_get(_id: int) -> ResourceFloor:
	return Resources.get_id_type(_id, SteeleResource.TYPE_FLOOR)

static func g_get_direction_texture(_id: int, dir: int) -> Texture2D:
	var r = Resources.get_id_type(_id, SteeleResource.TYPE_FLOOR)
	return r.get_direction_texture(dir) if r != null else null

