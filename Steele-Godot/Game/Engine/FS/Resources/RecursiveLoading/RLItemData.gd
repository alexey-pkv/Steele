extends Object
class_name RLItemData


var is_file: bool:
	get: return is_file

var is_dir: bool:
	get: return !is_file

var full_path: String:
	get: return full_path

var name: String:
	get: return full_path.get_file()


func _init(p_is_file: bool, p_full_path: String):
	full_path	= p_full_path
	is_file		= p_is_file

