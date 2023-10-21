extends RefCounted
class_name ResourceID


const SEPARATOR			= ":"
const PATH_SEPARATOR	= "/"


var m_parent:		ResourceID	= null
var m_id:			int			= 0

var m_path:			String = ""
var m_short_name:	String = ""
var m_module:		String
var m_module_path:	String
var m_local_path:	String = ""


var registry_id: int:
	get:
		if m_id == 0:
			m_id = IDMap.get_id(path)
		
		return m_id

var path: String:
	get:
		if m_path == "":
			if m_parent != null:
				m_path = m_parent.path + SEPARATOR + m_local_path
			else:
				m_path = m_module + SEPARATOR + m_module_path 
		
		return m_path

var short_name: String:
	get:
		if m_short_name == "":
			if m_parent != null:
				m_short_name = m_parent.short_name + SEPARATOR + m_local_path
			else:
				var parts = m_module_path.rsplit(PATH_SEPARATOR, true, 1)
				m_short_name = parts[-1] if len(parts) > 0 else ""
		
		return m_short_name

var module: String:
	get:
		return m_module if m_parent == null else m_parent.module

var module_path: String:
	get:
		return m_module_path if m_parent == null else m_parent.module_path

var local_name: String:
	get:
		return m_local_path if m_parent != null else ""

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
		id.local_path = m_local_path + SEPARATOR + local_path
	else:
		id.m_parent = self
		id.m_local_path = local_path
	
	return id
	
func register_child_i(index: int) -> int:
	return create_child(str(index)).register_id()
	
func register_child(local_path: String) -> int:
	return create_child(local_path).register_id()

func register_id() -> int:
	if m_id == 0:
		IDMap.add(path)
	
	return registry_id


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
	
	id.m_module = parts[0]
	id.m_module_path = parts[1]
	
	return id

static func cast(id) -> ResourceID:
	if id is String:
		return ResourceID.create(id)
	elif id is ResourceID:
		return id
	else:
		push_error("Invalid id!")
		return null
