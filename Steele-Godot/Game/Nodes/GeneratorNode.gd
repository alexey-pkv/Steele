extends Node
class_name GeneratorNode


@onready var m_generator: 	Generator	= $Generator
@onready var m_timer:		Timer		= $StatusTimer


var m_thread:			Thread
var m_db: 				ResourcesNode	= null
var m_map:				MapPatch		= null

var rng_state: RandomState		= null:
	get: return rng_state
	set(r): rng_state = r


func _get_configuration_warnings():
	return ["Scene incorrectly imported"] \
		if is_inside_tree() && get_child_count() == 0 else []


# First step
func _begin_generation(callback: Callable) -> void:
	abort(true)
	
	if m_map == null:
		on_end.emit(false)
		return
	elif m_db == null:
		m_db = Resources.get_resource_node()
	
	
	if rng_state != null:
		m_generator.set_rng_state(rng_state)
	
	m_generator.using_db(m_db.get_steele_db())
	m_generator.using_map_patch(m_map)
	
	m_thread = Thread.new()
	
	# Make sure thread object is set before emitting events.
	m_timer.start()
	on_begin.emit()
	
	m_thread.start(_execute_generation.bind(callback))

# Thread
func _execute_generation(callback: Callable) -> void:
	var result = callback.call()
	_handle_complete.call_deferred(result)

# Last step
func _handle_complete(result: bool) -> void:
	if m_thread == null:
		return
	
	m_thread = null
	
	m_map = null
	m_timer.stop()
	on_end.emit(result)


func _exit_tree():
	abort(true)


func using_map_patch(map: MapPatch) -> GeneratorNode:
	abort(true)
	m_generator.using_map_patch(map)
	return self

func using_db(db: ResourcesNode) -> GeneratorNode:
	abort(true)
	m_db = db
	return self

func using_rng_state(state: RandomState) -> GeneratorNode:
	abort(true)
	rng_state = state
	return self


func is_generating() -> bool:
	return m_thread != null;

func abort(wait: bool = false) -> bool:
	if m_thread == null:
		return true
	
	m_generator.abort()
	
	if !wait:
		return false
	
	m_thread.wait_to_finish()
	
	on_aborted.emit()
	_handle_complete(false)
	
	return true


func generate_brush(id: int, area: Area) -> void:
	_begin_generation(func (): 
		return m_generator.generate_brush(id, area))


func handle_timeout():
	if m_thread == null:
		m_timer.stop()
		return
	
	on_progress.emit(m_generator.get_progress())


signal on_begin
signal on_aborted
signal on_end(result: bool)
signal on_progress(progress: float)

