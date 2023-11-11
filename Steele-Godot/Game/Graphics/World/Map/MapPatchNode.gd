@tool
extends Node2D
class_name MapPatchNode


const SCENE_CellNode = preload("res://Game/Graphics/World/Map/CellNode.tscn")


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


@onready var m_map: MapPatch = MapPatch.new()

var m_grid: IsometricGrid:
	get: return $Grid


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
	get: return m_map.size()


func _create_cell() -> CellNode:
	return SCENE_CellNode.instantiate()


func _ready():
	m_grid.size = cell_size

func update_at(at: Vector3i) -> void:
	if !m_map.has_v3i(at):
		m_grid.remove_v3i(at)
		return
		
	var curr_node: CellNode = m_grid.get_at_v3i(at)
	var curr_cell: Cell = m_map.get_v3i(at)
	
	if curr_node == null:
		curr_node = _create_cell()
		m_grid.set_at_v3i(at, curr_node)
	
	var ground = curr_node.ground
	var tile: GroundTile = curr_cell.get_ground().tiles()[0]
	
	ground.direction = tile.direction
	ground.ground = tile.tile


func is_empty_v3(at: Vector3i) -> bool:
	return !m_map.has_v3i(at)

func try_get_at_v3(at: Vector3i) -> Cell:
	if !m_map.has_v3i(at):
		return null
		
	return m_map.get_v3i(at)
	
func get_at_v3(at: Vector3i) -> Cell:
	return m_map.get_v3i(at)
	
func get_at_v2(at: Vector2i, z: int = 0) -> Cell:
	return get_at_v3(Vector3i(at.x, at.y, z))
	
func set_at_v3(at: Vector3i, c: Cell) -> void:
	m_map.set_v3i(at, c)
	update_at(at)
	
func set_at_v2(at: Vector2i, c: Cell) -> void:
	set_at_v3(Vector3i(at.x, at.y, 0), c)
	
func create_at_v3(at: Vector3i) -> void:
	if m_map.has_v3i(at):
		return
	
	m_map.set_v3i(at, Cell.new())

func clear_at_v3(at: Vector3i) -> bool:
	if !m_map.remove_v3i(at):
		return false
	
	update_at(at)
	
	return true
	
func clear_at_v2(at: Vector2i, z: int = 0) -> bool:
	return clear_at_v3(Vector3i(at.x, at.y, z))

func clear() -> void:
	m_map.clear()
	m_grid.clear()


func handle_grid_mouse_motion(event: GridCellMotionArgs):
	on_hover.emit(event)

func handle_grid_mouse_click(event: GridCellButtonArgs):
	on_click.emit(event)


signal on_hover(event: GridCellMotionArgs)
signal on_click(event: GridCellButtonArgs)
