extends RefCounted
class_name ActorPath


@export var current_target: Vector3i	= Vector3i.ZERO
@export var direction_vector: Vector3i	= Vector3i.ZERO

@export var path: Array[Vector3i]		= []
@export var target_index				= 0

var points_count: int:
	get: return len(path)

var is_complete: bool:
	get: return target_index >= len(path)

var is_empty: bool:
	get: return len(path) == 0


func _set_target() -> void:
	current_target = path[target_index]
	
	direction_vector = Vector3(current_target - current_target)
	direction_vector = direction_vector.clamp(-Vector3i.ONE, Vector3i.ONE)


func next() -> bool:
	var count = len(path)
	
	if target_index >= count:
		return false
	
	target_index += 1
	
	if target_index == count:
		direction_vector = Vector3i.ZERO
		return false
	
	_set_target()
	
	return true

func start() -> bool:
	target_index = 0
	
	if len(path) == 0:
		return false
	
	_set_target()
	
	return true


func _init(_path: Array[Vector3i]):
	path = _path
