extends RefCounted
class_name AbstractRegistryObject


const TYPE_INVALID		= 0
const TYPE_GROUND_ATLAS	= 1


var m_type: int


var type:
	get: return m_type

var id: ResourceID:
	get:		return id
	set(value): id = value

var path: String:
	get: return id.path

 
func _init(p_id: ResourceID, p_type: int):
	id = p_id
	m_type = p_type


