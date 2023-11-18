extends Node
class_name ResourcesNode


var resources = {}
var resources_by_type = {}


func _ready():
	register()

func register() -> void:
	Resources.register(self)
	

func add_res(r: SteeleResource) -> void:
	resources[r.id] = r
	
	if !resources_by_type.has(r.type):
		resources_by_type[r.type] = { r.id: r }
	else:
		resources_by_type[r.type][r.id] = r
