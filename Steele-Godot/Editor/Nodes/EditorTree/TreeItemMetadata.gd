extends Resource
class_name TreeItemMetadata


@export var resource_id:	int		= SteeleID.NULL_ID
@export var folder:			String	= ""
@export var short_name:		String	= ""
@export var path:			String	= ""


var is_folder: bool:
	get: return resource_id == SteeleID.NULL_ID

var is_module: bool:
	get: return folder == ""

var is_resource: bool:
	get: return resource_id != SteeleID.NULL_ID

var resource: SteeleResource:
	get: return Resources.get_id(resource_id) if is_resource else null

func relative_path() -> String:
	return path.trim_prefix(SteeleResource.DEFULT_PATH)

func os_path() -> String:
	return OS.get_user_data_dir() + "/assets/" + relative_path()


func update(from: String, to: String) -> void:
	if folder == from:
		folder = to
	elif folder.begins_with(to + "/"):
		folder = folder.replace(from, to)

func rename(to: String) -> int:
	if to == short_name:
		return OK
	
	var old_name = short_name
	var old_path = path
	var res = OK
	
	short_name	= to
	
	if is_module:
		path = short_name
	else:
		path = folder + "/" + short_name
	
	if DirAccess.dir_exists_absolute(old_path):
		res = DirAccess.rename_absolute(old_path, path)
	else:
		res = DirAccess.make_dir_recursive_absolute(path)
	
	if res != OK:
		short_name	= old_name
		path		= old_path
	
	return res


static func create_from_resource(r: SteeleResource) -> TreeItemMetadata:
	var data = TreeItemMetadata.new()
	
	data.resource_id	= r.id
	data.folder			= r.folder
	data.short_name		= r.short_name
	data.path			= r.path
	
	return data

static func create_from_folder(p: TreeItemMetadata, n: String = "") -> TreeItemMetadata:
	var data = TreeItemMetadata.new()
	
	if p != null:
		data.folder		= p.path
		data.short_name = n
		data.path		= p.path + "/" + n
	else:
		data.folder		= ""
		data.short_name	= n
		data.path		= n
	
	return data
