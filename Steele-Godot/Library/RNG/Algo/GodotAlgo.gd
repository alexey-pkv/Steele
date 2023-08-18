extends IAlgo
class_name GodotAlgo


var _state: RandomNumberGenerator = null:
	set(value):
		_state = value
	get:
		if _state == null:
			_state = RandomNumberGenerator.new()
		
		return _state


func _init():
	_state.seed = 0


func next_int() -> int: 
	return _state.randi()

func next_int_range(from: int, to: int) -> int: 
	return _state.randi_range(from, to)

func next_float() -> float: 
	return _state.randf()

func next_float_range(from: float, to: float) -> float: 
	return _state.randf_range(from, to)


func randomize() -> void:
	_state.randomize()


func load(state: Dictionary) -> void:
	_state.seed = state['seed']

func save() -> Dictionary:
	return { 'seed': _state.seed }
