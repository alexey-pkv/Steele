@tool
extends Resource
class_name SteeleResource


const TYPE_UNDEFINED	= 0

const TYPE_FLOOR_ATLAS	= 1
const TYPE_FLOOR		= 2

const TYPE_TEXTURE			= 0b1_00000000_00000000
const TYPE_FLOOR_TEXTURE	= TYPE_TEXTURE | 1


@export var id: int = SteeleID.NULL:
	get: return id
	set(i): id = i

@export var name: String = ""
@export var path: String = ""
@export var module: String = ""
@export var parent_id: int = SteeleID.NULL
@export var is_valid: bool = true

@export var type: int = TYPE_UNDEFINED


var full_path: String:
	get: return module + ":" + path + ":" + name

var parent: SteeleResource: 
	get:
		return Resources.get_id(parent_id) if parent_id != SteeleID.NULL else null


func _init(_type: int = TYPE_UNDEFINED):
	if _type == TYPE_UNDEFINED:
		push_error("Type not defined!")
	
	type = _type



func get_path_parts() -> Array:
	var result = []
	
	for part in full_path.split('/', false):
		for sub_part in part.split(':', false):
			result.push_back(sub_part)
			
	return result

func setup_child(child: SteeleResource, _name: String) -> void:
	child.parent_id	= id
	child.module	= module
	child.path		= path + ":" + name
	child.name		= _name

func has_id() -> bool:
	return id != SteeleID.NULL

func has_parent() -> bool:
	return parent_id != SteeleID.NULL

func is_texture() -> bool:
	return type & TYPE_TEXTURE


static func _remove_prefix(p_path: String) -> String:
	var index = p_path.find(":/")
	
	if index < 0:
		return p_path
	
	return p_path.substr(index + 2)


func register(from_path: String = "") -> bool:
	if has_id():
		return true
	
	if from_path != "":
		from_path = Resources_Common.get_resource_path(from_path)
		from_path = SteeleResource._remove_prefix(from_path)
		
		var parts = from_path.split('/', false, 1)
		
		module = parts[0]
		parts = parts[-1].split('/', false, 1)
		path = parts[0] if len(parts) > 1 else ""
		name = parts[-1]
	
	return Resources.add_r(self)
	

func debug_data() -> String:
	return ""


func _to_string():
	var data = str(id)
	
	
	data += ":" + full_path + ":" + str(type)
	
	var debug = debug_data()
	
	if debug != "":
		data += " (" + debug + ")"
	
	return "SteelResource <" + data + ">"
