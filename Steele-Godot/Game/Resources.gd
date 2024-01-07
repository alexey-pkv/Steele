@tool
class_name Resources


func _init():
	push_error("Resources should not be initialized")


static var m_node: ResourcesNode = null


static func get_resource_node() -> ResourcesNode:
	return m_node

static func deregister(node: ResourcesNode) -> void:
	if m_node == node:
		m_node = null

static func register(node: ResourcesNode) -> void:
	if m_node != null:
		push_error("Global node already set: " + m_node.name)
		return
	
	var dest = func(): 
		deregister(node)
	
	node.tree_exiting.connect(dest, CONNECT_ONE_SHOT)
	m_node = node


static func has(id: int) -> bool:
	return m_node.resources.has(id) if m_node != null else false

static func get_id(id: int) -> SteeleResource:
	return m_node.resources.get(id) if m_node != null else null

static func get_id_type(id: int, type: int) -> SteeleResource:
	var res = get_id(id)
	
	if res != null && res.type == type:
		return res
	
	return null

static func validate_type(id: int, type: int) -> bool:
	var res = get_id(id)
	return res != null && res.type == type

static func add_r(r: SteeleResource) -> bool:
	if r.has_id():
		push_error("Resource already registered!")
		return false
	elif m_node == null:
		push_error("Resources node not set!")
		return false
	
	r.id = SteeleID.next()
	m_node.add_res(r)
	
	return true

static func get_texture(id: int) -> Texture:
	var r = get_id(id)
	
	if r == null:
		push_error("Resource with id " + str(id) + " does nto exists")
	elif !r.is_texture():
		push_error("Resource " + str(id) + " does nto exists")
	elif r.texture == null:
		push_error("Resource " + str(id) + " missing a texture")
	
	return r.texture

static func get_all_of_type(type: int) -> Dictionary:
	if m_node == null:
		return {}
	
	if !m_node.resources_by_type.has(type):
		return {}
	
	return m_node.resources_by_type[type]
