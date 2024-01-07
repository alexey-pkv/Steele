extends Node
class_name ResourcesNode


var resources = {}
var resources_by_type = {}


@onready var m_db: ResourcesDBNode = $DB


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


func _register_in_db(r: SteeleResource) -> void:
	if r is ResourceFillBrush:
		m_db.add_fill_brush(r.id, r.config)


func _ready():
	register()


func get_steele_db() -> ResourcesDBNode:
	return m_db

func register() -> void:
	if Engine.is_editor_hint():
		return
	
	Resources.register(self)

func add_res(r: SteeleResource) -> void:
	resources[r.id] = r
	
	if !resources_by_type.has(r.type):
		resources_by_type[r.type] = { r.id: r }
	else:
		resources_by_type[r.type][r.id] = r
