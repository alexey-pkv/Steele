@tool
extends Node2D
class_name MapPatchNode


const SCENE_CellNode = preload("res://Game/Graphics/World/Map/CellNode.tscn")


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


@onready var m_grid: IsometricGrid = $Grid


@export var is_debug: bool = false:
	get: return is_debug
	set(v): 
		is_debug = v
		
		if is_inside_tree():
			$dbg.visible = v

@export var mouse_control_node: Control:
	get: return $GridMouseEventsNode.mouse_control_node
	set(n): 
		if $GridMouseEventsNode != null:
			$GridMouseEventsNode.mouse_control_node = n

@export var cell_size: Vector3i = Vector3i(32, 16, 0): 
	get: return cell_size
	set(v): 
		cell_size = v
		
		if is_inside_tree():
			m_grid.size = cell_size


var count: int:
	get: return m_grid.count


func _create_cell() -> CellNode:
	return SCENE_CellNode.instantiate()


func _ready():
	m_grid.size = cell_size

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
	
func get_at_v2(at: Vector2i, z: int = 0) -> CellNode:
	return get_at_v3(Vector3i(at.x, at.y, z))
	
func create_at_v3(at: Vector3i) -> void:
	if m_grid.has_v3i(at):
		return
	
	m_grid.set_at_v3i(at, _create_cell())

func clear_at_v3(at: Vector3i) -> bool:
	print(at)
	
	
	return m_grid.remove_v3i(at)
	
func clear_at_v2(at: Vector2i, z: int = 0) -> bool:
	return m_grid.remove_v3i(Vector3i(at.x, at.y, z))

func clear() -> void:
	m_grid.clear()


func handle_grid_mouse_motion(event: GridCellMotionArgs):
	on_hover.emit(event)

func handle_grid_mouse_click(event: GridCellButtonArgs):
	on_click.emit(event)


signal on_hover(event: GridCellMotionArgs)
signal on_click(event: GridCellButtonArgs)
