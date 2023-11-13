extends RefCounted
class_name ResourceID


const SEPARATOR			= ":"
const PATH_SEPARATOR	= "/"


var m_parent:		ResourceID	= null


var registry_id: int:
	get:
		if registry_id == 0:
			registry_id = IDMap.get_id(path)
		
		return registry_id

var path: String:
	get:
		if path == "":
			if m_parent != null:
				path = m_parent.path + SEPARATOR + local_name
			else:
				path = module + SEPARATOR + module_path 
		
		return path

var short_name: String:
	get:
		if short_name == "":
			if m_parent != null:
				short_name = m_parent.short_name + SEPARATOR + local_name
			else:
				var parts = module_path.rsplit(PATH_SEPARATOR, true, 1)
				short_name = parts[-1] if len(parts) > 0 else ""
		
		return short_name

var module: String:
	get:
		return module if m_parent == null else m_parent.module

var module_path: String:
	get:
		return module_path if m_parent == null else m_parent.module_path

var local_name: String:
	get:
		return local_name if m_parent != null else ""

var is_child: bool:
	get:
		return m_parent != null
		
var is_parent: bool:
	get:
		return m_parent == null

func create_child_i(index: int) -> ResourceID:
	return create_child(str(index))
	
func create_child(local_path: String) -> ResourceID:
	var id = ResourceID.new()
	
	if m_parent != null:
		id.m_parent = m_parent
		id.local_path = local_name + SEPARATOR + local_path
	else:
		id.m_parent = self
		id.local_name = local_path
	
	return id
	
func register_child_i(index: int) -> int:
	return create_child(str(index)).register_id()
	
func register_child(local_path: String) -> int:
	return create_child(local_path).register_id()

func register_id() -> int:
	if registry_id == 0:
		registry_id = IDMap.add(path)
	
	return registry_id

func get_path_parts() -> Array:
	var result = []
	
	for part in path.split(PATH_SEPARATOR, false):
		for sub_part in part.split(SEPARATOR, false):
			result.push_back(sub_part)
			
	return result

func equals(to) -> bool:
	if !(to is ResourceID):
		return false
	
	return self == to || path == to.path

func get_parent() -> ResourceID:
	return m_parent

static func _remove_prefix(p_path: String) -> String:
	var index = p_path.find(":/")
	
	if index < 0:
		return p_path
	
	return p_path.substr(index + 2)
		

static func create(p_path: String) -> ResourceID:
	p_path = _remove_prefix(p_path)
	
	var parts = p_path.split(PATH_SEPARATOR, false, 1)
	
	if len(parts) != 2:
		return null
	
	var id = ResourceID.new()
	
	id.module = parts[0]
	id.module_path = parts[1]
	
	return id

static func cast(id) -> ResourceID:
	if id is String:
		return ResourceID.create(id)
	elif id is ResourceID:
		return id
	else:
		push_error("Invalid id!")
		return null
