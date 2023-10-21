extends RefCounted
class_name AsyncState


var m_on_complete: Array[Callable] = []


var total_calls: int:
	get: return total_calls

var should_run: bool = true:
	get: return should_run

var pending_count: int:
	get: return pending_count


func _complete() -> void:
	if pending_count != 0:
		return
	
	for c in m_on_complete:
		c.call_deferred()
	
	m_on_complete.clear()

func _execute_callback(c: Callable) -> void:
	if should_run:
		total_calls += 1
		c.call()
	
	pending_count -= 1
	
	if pending_count == 0:
		_complete.call_deferred()
	elif pending_count < 0:
		push_error("OY VEY! this should not be happening! pending_count < 0 in AsyncState")

func on_complete(c: Callable) -> void:
	m_on_complete.push_back(c)
	_complete.call_deferred()

func abort() -> void:
	should_run = false

func defer_callback(c: Callable) -> void:
	if !should_run:
		return
	
	pending_count += 1
	_execute_callback.call_deferred(c)


func is_complete() -> bool:
	return pending_count == 0

