extends Node
class_name GameResourcesScene


var c_textures_registry: TexturesRegistryNode:
	get:
		return $TexturesRegistryNode

var c_templates_registry: TemplatesRegistryNode:
	get:
		return $TemplatesRegistryNode


func load_file(path: String) -> void:
	var id: ResourceID
	
	if Loader_Floor.is_floor(path):
		id = Loader_Floor.load_floor(path)
	else:
		push_error("Unexpected file type for " + path)
		return 
	
	if id != null:
		on_resource_loaded.emit(id)
	else:
		on_failed_to_load.emit(path)


func _init_globals() -> void:
	if c_textures_registry != null:
		c_textures_registry.set_global()

	if c_templates_registry != null:
		c_templates_registry.set_global()


func _enter_tree():
	_init_globals()
	
func _ready():
	_init_globals()

func _exit_tree():
	if c_textures_registry != null:
		c_textures_registry.unset_global()
		c_textures_registry.queue_free()
	
	if c_templates_registry != null:
		c_templates_registry.unset_global()
		c_templates_registry.queue_free()


signal on_failed_to_load(path: String)
signal on_resource_loaded(id: ResourceID)










