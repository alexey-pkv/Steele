@tool
extends Node2D
class_name MapPatchNode


const SCENE_CellNode = preload("res://Game/Graphics/World/Map/CellNode.tscn")


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


@onready var m_grid: IsometricGrid = $Grid


@export var cell_size: Vector3i = Vector3i(32, 16, 0): 
	get: return cell_size
	set(v): 
		cell_size = v
		
		if is_inside_tree():
			m_grid.size = cell_size


var count: int:
	get: return m_grid.count


func _create_cell() -> CellNode:
	var cell: CellNode = SCENE_CellNode.instantiate();
	
	cell.cell_size = cell_size
	
	return cell


func is_empty_v3(at: Vector3i) -> bool:
	return m_grid.is_empty_v3i(at)

func try_get_at_v3(at: Vector3i) -> CellNode:
	return m_grid.get_at_v3i(at)
	
func get_at_v3(at: Vector3i) -> CellNode:
	var res = m_grid.get_at_v3i(at)
	
	if res == null:
		res = _create_cell()
		m_grid.set_at_v3i(at, res)
	
	return res
	
func create_at_v3(at: Vector3i) -> void:
	if m_grid.has_v3i(at):
		return
	
	m_grid.set_at_v3i(at, _create_cell())

func clear_at_v3(at: Vector3i) -> bool:
	return m_grid.remove_v3i(at)

func clear() -> void:
	m_grid.clear()



