@tool
extends Resource
class_name SteeleResource


const DEFULT_PATH		= "user://assets/"

const TYPE_UNDEFINED	= 0

const TYPE_FLOOR_ATLAS	= 1
const TYPE_FLOOR		= 2
const TYPE_PALETTE		= 3

const TYPE_TEXTURE			= 0b00000001_00000000_00000000
const TYPE_BRUSH			= 0b00000010_00000000_00000000

const TYPE_FLOOR_TEXTURE	= TYPE_TEXTURE | 1

const TYPE_BRUSH_FILL		= TYPE_BRUSH | 1


@export var id: int = SteeleID.NULL_ID:
	get: return id
	set(i): id = i

@export var short_name: String
@export var path: String = ""
@export var folder: String = ""
@export var module: String = ""
@export var parent_id: int = SteeleID.NULL_ID
@export var is_valid: bool = true
@export var type: int = TYPE_UNDEFINED


var relative_path: String:
	get: return path.trim_prefix(DEFULT_PATH)

var is_file: bool: 
	get: return folder != ""

var parent: SteeleResource: 
	get:
		return Resources.get_id(parent_id) if parent_id != SteeleID.NULL_ID else null


func _init(_type: int = TYPE_UNDEFINED):
	if _type == TYPE_UNDEFINED:
		push_error("Type not defined!")
	
	type = _type

func define_path(_path: String) -> void:
	path = _path
	
	var parts = path.trim_prefix(DEFULT_PATH).split("/", false)
	
	if len(parts) == 1:
		module = ""
		short_name = parts[0]
		folder = ""
		return

	module = parts[0]
	short_name = parts[-1]
	folder = _path.trim_suffix("/" + short_name)

func get_path_parts() -> Array:
	return path.trim_prefix(DEFULT_PATH).split('/', false)

func setup_child(child: SteeleResource, _name: String) -> void:
	child.parent_id		= id
	child.path			= path + ":" + _name
	child.short_name	= _name
	child.folder		= ""
	child.module		= module

func has_id() -> bool:
	return id != SteeleID.NULL_ID

func has_parent() -> bool:
	return parent_id != SteeleID.NULL_ID

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
		define_path(from_path)
	
	return Resources.add_r(self)

func rename_partial(old_prefix: String, new_prefix: String) -> bool:
	if !path.begins_with(old_prefix):
		return false
	
	define_path(new_prefix + path.trim_prefix(old_prefix))
	
	return true
	

func debug_data() -> String:
	return ""


func _to_string():
	var data = str(id)
	
	data += ":" + path + ":" + str(type)
	
	var debug = debug_data()
	
	if debug != "":
		data += " (" + debug + ")"
	
	return "SteelResource <" + data + ">"
