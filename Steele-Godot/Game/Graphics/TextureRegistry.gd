class_name TextureRegistry


static var m_registry : Dictionary = {}


static func get_texture_type(type: int, id: int, i = null) -> Texture2D:
	if !m_registry.has(id):
		return null
	
	var ref: TextureRef = m_registry[id]
	
	return ref.get_texture_for_type(type, i)

static func get_texture(id: int) -> Texture2D:
	return get_texture_type(TextureRef.TYPE_TEXTURE, id)
	
static func get_ground(id: int, dir: int) -> Texture2D:
	return get_texture_type(TextureRef.TYPE_GROUND, id, dir)

static func add_texture(id: int, ref: TextureRef) -> void:
	m_registry[id] = ref

static func add_ground_textures(atlas: Texture2D, id, rows: int) -> ResourceID:
	var size = atlas.get_size()
	
	id = ResourceID.cast(id)
	
	size.x = size.x / 4
	size.y = size.y / rows
	
	for i in range(0, rows + 1):
		add_texture(
			id.register_child_i(i),
			TextureRef.create_ground_ref(atlas, i, size)
		)
	
	return id
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
