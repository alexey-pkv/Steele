@tool
extends Node2D
class_name Actor


#region Warnings/Debug

func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []

@export var debug:			bool = false:
	get: return debug
	set(v):
		debug = v
		
		if is_inside_tree():
			if v:
				_start_debug()
			else:
				_end_debug()

func _start_debug() -> void:
	$DebugInfo.text = str(actor_id) + ": " + actor_name
	$DebugInfo.visible = true

func _end_debug() -> void:
	$DebugInfo.visible = false

#endregion


var path: ActorPath = null


@export var actor_name:		String		= ""
@export var actor_id:		int			= 0

@export var at_cell:	Vector3i	= Vector3i.ZERO
@export var at_pos:		Vector3		= Vector3i.ZERO

@export var target_cell:	Vector3i	= Vector3i.ZERO
@export var target_pos:		Vector3		= Vector3.ZERO

@export var speed:			float		= 3
@export var direction:		Vector3i	= Vector3i.ZERO
@export var world_speed:	Vector3		= Vector3.ZERO

@export var is_moving:		bool		= false


var has_path: bool:
	get: return path != null


#region Driver Methods

# Unset all target settings
func _unset_movement() -> bool:
	if !is_moving: return false
	
	path = null
	is_moving = false
	
	target_cell	= Vector3i.ZERO
	target_pos	= Vector3.ZERO
	
	direction	= Vector3i.ZERO
	world_speed	= Vector3.ZERO
	
	return true

func _set_direction(dir: Vector3i) -> void:
	direction = dir
	world_speed = Vector3(dir.x * speed, dir.y * speed, dir.z * speed)

func _set_target_cell(to: Vector3i, dir: Vector3i) -> void:
	is_moving = true
	
	target_cell	= to
	target_pos	= Vector3(to)
	
	_set_direction(dir)

func _reset_target_cell() -> void:
	_set_target_cell_and_dir(target_cell)

func _set_target_cell_and_dir(to: Vector3i) -> void:
	var dir = Vectors.get_direction_vector_v3(to - at_cell)
	_set_target_cell(to, dir)

func _set_path_target() -> void:
	_set_target_cell(path.current_target, path.direction_vector)

func _continue_path() -> bool:
	if path == null || !path.next():
		return false
	
	_set_target_cell(path.current_target, path.direction_vector)
	
	return true

func _update_position() -> void:
	position = Game.world_position_to_real_position(at_pos)

func _reset_position() -> void:
	_place_at_cell(at_cell)

func _place_at_cell(at: Vector3i) -> void:
	at_cell = at
	at_pos	= at
	
	_update_position()

func _stop_and_trigger_move_events() -> void:
	var was_moving = _unset_movement()
	_trigger_move_events(was_moving)

func _trigger_move_events(was_moving: bool) -> void:
	if was_moving || is_moving:
		on_move_update.emit(actor_id)
		
		if was_moving && !is_moving:
			on_move_end.emit(actor_id)
		elif !was_moving && is_moving:
			on_move_begin.emit(actor_id)

#endregion

#region Private Methods

func _update_pos(pos: Vector3) -> void:
	var new_cell = Vector3i(pos)
	
	if at_pos == pos:
		return
	
	at_pos = pos
	_update_position()
	
	if at_cell != new_cell:
		var old_cell = at_cell
		at_cell = new_cell
		
		on_arrived_at_cell.emit(actor_id, old_cell, new_cell)

#endregion

func _ready():
	if debug:
		_start_debug()

func _process(delta: float):
	if !is_moving || Game.is_paused(): return
	
	var change = world_speed * delta
	var change_length = change.length()
	var max = target_pos - at_pos
	
	if change == Vector3.ZERO:
		return
	elif change.length() >= max.length():
		_place_at_cell(target_cell)
		
		if !_continue_path():
			_stop_and_trigger_move_events()
	else:
		_update_pos(at_pos + change)


#region Public Methods

func set_speed(s: float) -> void:
	speed = s
	
	if direction != Vector3i.ZERO:
		_set_direction(direction)

## Should be called only onces, when creating and placing a new actor
func init_position(at: Vector3i) -> void:
	if at_cell == at:
		return
	
	_unset_movement()
	_place_at_cell(at)
	
	on_arrived_at_cell.emit(actor_id, at, at)

func init_position_v2i(at: Vector2i) -> void:
	init_position(Vector3i(at.x, at.y, 0))

func init_position_xyz(x: int, y: int, z: int = 0) -> void:
	init_position(Vector3i(x, y, z))

## Immidietly place an actor at a position
func place_at(at: Vector3i) -> void:
	var was_moving = _unset_movement()
	var prev_at = at_cell
	
	_place_at_cell(at)
	
	if prev_at != at:
		on_arrived_at_cell.emit(actor_id, prev_at, at)
	
	_trigger_move_events(was_moving)
	
func place_at_v2i(at: Vector2i) -> void:
	place_at(Vector3i(at.x, at.y, 0))

func move_to(to_cell: Vector3i) -> bool:
	var was_moving = _unset_movement()
	var result = true
	
	_reset_position()
	
	if !is_valid_target(to_cell):
		on_invalid_target.emit(actor_id, to_cell, null)
		result = false
	else:
		if to_cell != at_cell:
			_set_target_cell_and_dir(to_cell)
	
	_trigger_move_events(was_moving)
	
	return result
	
func move_to_v2i(to: Vector2i) -> void:
	move_to(Vector3i(to.x, to.y, 0))

func move_to_xyz(x: int, y: int, z: int = 0) -> void:
	move_to(Vector3i(x, y, z))

func move_via(via: ActorPath) -> bool:
	var was_moving = _unset_movement()
	var result = true
	
	_reset_position()
	
	if via.is_empty:
		result = false
	elif !is_valid_target(via.current_target):
		on_invalid_target.emit(actor_id, via.current_target, via)
		result = false
	else:
		path = via
		_set_path_target()
	
	_trigger_move_events(was_moving)
	
	return result

## Move to the current target and reset movement.
func jump_to_target() -> void:
	if !is_moving: return
	
	place_at(target_cell)

func cancel_movement() -> void:
	var was_moving = _unset_movement()
	
	_reset_position()
	_trigger_move_events(was_moving)


func is_moving_towards() -> bool:
	if !is_moving: return false
	
	var diff = Vector3(at_cell) - at_pos
	var diff_dir = Vectors.get_direction_vector_v3(diff)
	
	return diff_dir == direction

func is_moving_away() -> bool:
	if !is_moving: return false
	
	return !is_moving_towards()

func is_valid_target(target: Vector3i) -> bool:
	var diff = abs(at_cell - target)
	var scalar_diff
	
	if diff.x:		scalar_diff = diff.x
	elif diff.y:	scalar_diff = diff.y
	elif diff.z:	scalar_diff = diff.z
	
	return \
		(diff.x == 0 || diff.x == scalar_diff) && \
		(diff.y == 0 || diff.y == scalar_diff) && \
		(diff.z == 0 || diff.z == scalar_diff)

#endregion

#region Events

signal on_arrived_at_cell(id: int, from: Vector3i, to: Vector3i)

signal on_invalid_target(id: int, target: Vector3i, path: ActorPath)

signal on_move_update(id: int)
signal on_move_begin(id: int)
signal on_move_end(id: int)

#endregion
