extends Node
class_name TexturesRegistryNode


var m_registry : Dictionary = {}


var registry: Dictionary:
	get: return m_registry


func get_texture_type(type: int, id: int, i = null) -> Texture2D:
	if !m_registry.has(id):
		return null
	
	var ref: TextureRef = m_registry[id]
	
	return ref.get_texture_for_type(type, i)

func get_texture(id: int) -> Texture2D:
	return get_texture_type(TextureRef.TYPE_TEXTURE, id)
	
func get_ground(id: int, dir: int) -> Texture2D:
	return get_texture_type(TextureRef.TYPE_GROUND, id, dir)

func add_texture(id: int, ref: TextureRef) -> void:
	m_registry[id] = ref

func add_ground_textures(atlas: Texture2D, id: ResourceID, rows: int) -> ResourceID:
	var size = atlas.get_size()
	
	id = ResourceID.cast(id)
	
	size.x = size.x / 4
	size.y = size.y / rows
	
	add_texture(id.register_id(), TextureRef.create_static_ref(atlas))
	
	for i in range(0, rows + 1):
		add_texture(
			id.register_child_i(i),
			TextureRef.create_ground_ref(atlas, i, size)
		)
	
	return id
	

static var __MAIN_REGISTRY__: TexturesRegistryNode = null

func set_global() -> void:
	if __MAIN_REGISTRY__ != null:
		if __MAIN_REGISTRY__ != self:
			push_error("Global Texture registry already set!")
	else:
		__MAIN_REGISTRY__ = self

func unset_global() -> void:
	if __MAIN_REGISTRY__ == self:
		__MAIN_REGISTRY__ = null

func is_global() -> bool:
	return __MAIN_REGISTRY__ == self

static func global() -> TexturesRegistryNode:
	return __MAIN_REGISTRY__

static func has_glboal() -> bool:
	return __MAIN_REGISTRY__ != null

func _exit_tree():
	unset_global()
	queue_free()
	
	
	
static func g_get_texture_type(type: int, id: int, i = null) -> Texture2D:
	return global().get_texture_type(type, id, i)

static func g_get_texture(id: int) -> Texture2D:
	return global().get_texture(id)

static func g_get_ground(id: int, dir: int) -> Texture2D:
	return global().get_ground(id, dir)

static func g_add_texture(id: int, ref: TextureRef) -> void:
	global().add_texture(id, ref)

static func g_add_ground_textures(atlas: Texture2D, id: ResourceID, rows: int) -> ResourceID: 
	return global().add_ground_textures(atlas, id, rows)
	
	
	
	
	
	
	
	
