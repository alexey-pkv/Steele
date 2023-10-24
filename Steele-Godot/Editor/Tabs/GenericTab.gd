extends Control
class_name GenericTab


var resource_id: ResourceID:
	get: return resource_id
	set(id): resource_id = id


func load_resource() -> void:
	push_error("Must be implemented!!!")


signal on_error(message: String, id: ResourceID)
