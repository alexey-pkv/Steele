extends Node
class_name WorldDataNode


const GROUP_NAME	= "world_data"


var m_direction: int = Direction.NORTH


var direction: int:
	get:
		return m_direction
	set(value):
		m_direction = Direction.dir_ceil(value)


func _enter_tree() -> void:
	add_to_group(GROUP_NAME)


static func get_world(node: Node) -> WorldDataNode:
	var tree = node.get_tree()
	
	if tree == null:
		return null
	
	return tree.get_first_node_in_group(GROUP_NAME)

static func get_direction(node: Node, dir: int = Direction.NORTH) -> int:
	var tree = node.get_tree()
	
	if tree == null:
		return dir
	
	var data: WorldDataNode = tree.get_first_node_in_group(GROUP_NAME)
	
	if data == null:
		return dir
	
	return Direction.add(dir, data.direction)
