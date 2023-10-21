extends RefCounted
class_name TextureDataRegistry


var m_registry: Dictionary = {}


var count: int:
	get: return len(m_registry)

var registry: Dictionary:
	get: return m_registry

var is_empty: bool:
	get: return m_registry.is_empty()


func add_atlas(atlas: AtlasData) -> void:
	m_registry[atlas.path] = atlas

func get_data(path: String) -> AbstractRegistryObject:
	if !has_data(path): 
		return null
	
	return m_registry[path]
	
func get_data_type(path: String) -> int:
	var item = get_data(path)
	
	return item.type if item != null else -1

func get_data_of_type(path: String, type: int) -> AbstractRegistryObject:
	var item = get_data(path)
	
	if item == null || item.type != type:
		return null
		
	return item
	
func has_data(path: String) -> bool:
	return m_registry.has(path)
	
func has_data_of_type(path: String, type: int) -> bool:
	return get_data_of_type(path, type) != null

func has_ground_atlas(path: String) -> bool:
	return has_data_of_type(path, AbstractRegistryObject.TYPE_GROUND_ATLAS)
	
func get_ground_atlas(path: String) -> AtlasData:
	return get_data_of_type(path, AbstractRegistryObject.TYPE_GROUND_ATLAS)
	
func get_ground_atlas_id(id: ResourceID) -> AtlasData:
	if id == null: 
		return null
	
	return get_data_of_type(id.path, AbstractRegistryObject.TYPE_GROUND_ATLAS)

func clear() -> void:
	m_registry.clear()

