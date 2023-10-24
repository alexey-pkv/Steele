extends Node
class_name TemplatesRegistryNode



var m_registry: Dictionary = {}


var count: int:
	get: return len(m_registry)

var registry: Dictionary:
	get: return m_registry

var is_empty: bool:
	get: return m_registry.is_empty()


func _get_path(of) -> String:
	if of is String:
		return of
	elif of == null:
		return ""
	else:
		return of.path


func add_atlas(atlas: AtlasData) -> void:
	m_registry[atlas.path] = atlas

func get_data(id) -> AbstractRegistryObject:
	var path = _get_path(id)
	
	if !has_data(path): 
		return null
	
	return m_registry[path]
	
func get_data_type(id) -> int:
	var item = get_data(id)
	return item.type if item != null else TemplateType.TYPE_INVALID

func get_data_by_type(id, type: int) -> AbstractRegistryObject:
	var item = get_data(id)
	
	if item == null || item.type != type:
		return null
		
	return item
	
func has_data(id) -> bool:
	return m_registry.has(_get_path(id))
	
func has_ground_atlas(id) -> bool:
	return get_data_by_type(id, TemplateType.TYPE_GROUND_ATLAS) != null
	
func get_ground_atlas(id) -> AtlasData:
	return get_data_by_type(id, TemplateType.TYPE_GROUND_ATLAS)
	

func clear() -> void:
	m_registry.clear()


static var __MAIN_REGISTRY__: TemplatesRegistryNode = null

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

static func global() -> TemplatesRegistryNode:
	return __MAIN_REGISTRY__

static func has_glboal() -> bool:
	return __MAIN_REGISTRY__ != null


func _exit_tree():
	m_registry.clear()
	unset_global()
	queue_free()


static func g_add_atlas(atlas: AtlasData) -> void:
	__MAIN_REGISTRY__.add_atlas(atlas)
