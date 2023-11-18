@tool
extends Control
class_name AbstractResourceExplorerItem


var resource_id: int:
	get: return resource_id
	set(v): 
		if resource_id != v:
			resource_id = v
			_update()


func _update() -> void:
	pass

