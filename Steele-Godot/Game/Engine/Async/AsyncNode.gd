extends Node
class_name AsyncNode


var m_state: AsyncState = AsyncState.new()


var state: AsyncState:
	get: return m_state


var total_calls: int: 
	get: return m_state.total_calls
	
var should_run: bool: 
	get: return m_state.should_run
	
var pending_count: int: 
	get: return m_state.pending_count


func on_complete(c: Callable) -> void:
	m_state.on_complete(c)

func abort() -> void:
	m_state.abort()

func defer_callback(c: Callable) -> void:
	m_state.defer_callback(c)

func is_complete() -> bool:
	return m_state.is_complete()

func reset() -> void:
	m_state.reset()


func _exit_tree():
	abort()
