extends Resource
class_name TreeItemMetadata


@export var resource_id:	int		= SteeleID.NULL
@export var folder:			String
@export var item_name:		String


var has_folder: bool:
	get: return folder != ""

var is_folder: bool:
	get: return resource_id == SteeleID.NULL

var is_module: bool:
	get: return !folder.contains("/")

var is_resource: bool:
	get: return resource_id != SteeleID.NULL

var relative_path: String:
	get:
		if has_folder:
			return folder + "/" + item_name
		else:
			return item_name

var full_path: String:
	get: return OS.get_user_data_dir() + "/assets/" + relative_path

var user_path: String:
	get: return "user://assets/" + relative_path


func update(from: String, to: String) -> void:
	if folder == from:
		folder = to
	elif folder.begins_with(to + "/"):
		folder = folder.replace(from, to)

func rename(to: String) -> int:
	if to == item_name:
		return OK
	
	var old_name = item_name
	var old_path = full_path
	var res = OK
	
	item_name = to
	
	if DirAccess.dir_exists_absolute(old_path):
		res = DirAccess.rename_absolute(old_path, full_path)
	else:
		res = DirAccess.make_dir_recursive_absolute(full_path)
	
	if res != OK:
		item_name = old_name
	
	return res


static func create_from_resource(r: SteeleResource) -> TreeItemMetadata:
	var data = TreeItemMetadata.new()
	
	data.resource_id	= r.id
	data.folder			= r.file_path
	data.item_name		= r.name
	
	return data

static func create_from_folder(p, n: String = "") -> TreeItemMetadata:
	var data = TreeItemMetadata.new()
	
	if p == null:
		p = ""
	
	if p is TreeItemMetadata:
		data.folder = p.relative_path
		data.item_name = n
	elif n != "":
		data.folder		= p
		data.item_name	= n
	else:
		var parts = p.rsplit('/', true, 1)
		
		if len(parts) == 1:
			data.folder		= ""
			data.item_name	= p
		else:
			data.folder		= parts[0]
			data.item_name	= parts[1]
	
	return data
	
