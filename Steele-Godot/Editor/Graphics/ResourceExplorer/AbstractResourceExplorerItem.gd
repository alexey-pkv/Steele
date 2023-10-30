@tool
extends Control
class_name AbstractResourceExplorerItem


var resource_id: ResourceID:
	get: return resource_id
	set(v): 
		resource_id = v
		_update()


func _update() -> void:
	pass

