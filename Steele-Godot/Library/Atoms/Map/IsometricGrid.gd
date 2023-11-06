@tool
extends Node2D
class_name IsometricGrid


var m_size:	Vector3i
var m_map:	Dictionary = {}


var count: int:
	get: return m_map.size()

@export var size: Vector3i:
	set(v):
		m_size = v
	get:
		return m_size


func is_empty_z0(x: int, y: int) -> bool:
	return is_empty_v3i(Vector3i(x, y, 0))
	
func is_empty(x: int, y: int, z: int) -> bool:
	return is_empty_v3i(Vector3i(x, y, z))

func is_empty_v3i(at: Vector3i) -> bool:
	return !m_map.has(at)

func has_z0(x: int, y: int) -> bool:
	return has_v3i(Vector3i(x, y, 0))

func has(x: int, y: int, z: int) -> bool:
	return has_v3i(Vector3i(x, y, z))

func has_v2i(at: Vector2i) -> bool:
	return has_v3i(Vector3i(at.x, at.y, 0))

func has_v3i(at: Vector3i) -> bool:
	return m_map.has(at)

func clear() -> void:
	m_map.clear()
	
	for child in get_children():
		child.queue_free()

func get_at_z0(x: int, y: int) -> Node:
	return get_at_v3i(Vector3i(x, y, 0))

func get_at(x: int, y: int, z: int) -> Node:
	return get_at_v3i(Vector3i(x, y, z))

func get_at_v2i(at: Vector2i) -> Node:
	return get_at_v3i(Vector3i(at.x, at.y, 0))
	
func get_at_v3i(at: Vector3i) -> Node:
	if !m_map.has(at):
		return null
	
	return m_map[at]

func set_at_z0(x: int, y: int, n: Node) -> void:
	set_at_v3i(Vector3i(x, y, 0), n)

func set_at(x: int, y: int, z: int, n: Node) -> void:
	set_at_v3i(Vector3i(x, y, z), n)

func set_at_v3i(v: Vector3i, n: Node) -> void:
	if has_v3i(v):
		var curr = get_at_v3i(v)
		
		if curr == n:
			return
		
		remove_v3i(v)
	
	n.position = Isometric.grid_to_local(v, m_size)
	
	m_map[v] = n
	add_child(n)

func remove_z0(x: int, y: int) -> bool:
	return remove_v3i(Vector3i(x, y, 0))

func remove(x: int, y: int, z: int) -> bool:
	return remove_v3i(Vector3i(x, y, z))

func remove_v3i(v: Vector3i) -> bool:
	if !m_map.has(v):
		return false
	
	var n: Node = m_map[v]
	
	m_map.erase(v)
	n.queue_free()
	
	return true

func global_to_grid(global: Vector2) -> Vector2i:
	return local_to_grid(to_local(global))
	
func local_to_grid(local: Vector2) -> Vector2i:
	return Isometric.local_to_grid(local, m_size)

func grid_to_local(local: Vector2i) -> Vector2:
	return Isometric.grid_to_local(Vector3i(local.x, local.y, 0), m_size)

