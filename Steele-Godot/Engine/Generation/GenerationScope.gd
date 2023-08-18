class_name GenerationScope


const HISTORY_SIZE	= 256


var rng:		RNG
var variables:	GenerationVariables	= GenerationVariables.new()


var stack_history:			Array[String]	= []
var gen_stack:				Array[String]	= []
var error_message:			String			= ""
var continue_generation:	bool			= true
var is_aborted:				bool			= false


var abort_generation: bool:
	get:
		return not continue_generation

var is_failed: bool:
	get: 
		return error_message != ""


func _history_add(val: String) -> void:
	stack_history.push_back(val)
	
	while len(stack_history) > HISTORY_SIZE:
		stack_history.pop_front()
		
func _history_push(val: String) -> void:
	_history_add("push: " + val)
	
func _history_pop(val: String) -> void:
	_history_add("pop : " + val)


func init_rng(algo: IAlgo, seed: String) -> void:
	rng = RNG.new(algo, seed)


func set_error(message: String) -> void:
	if is_aborted:
		return
	
	error_message = message
	continue_generation = false
	return

func abort() -> void:
	continue_generation = false
	is_aborted = true

func push_gen_stack(action: String) -> void:
	if not continue_generation:
		return
	
	gen_stack.push_back(action)
	_history_push(action)


func pop_gen_stack() -> bool:
	if not continue_generation:
		return false
	
	if len(gen_stack) == 0:
		push_error("Pop called for an empty stack!")
		return false
	
	_history_pop(gen_stack.pop_back())
	
	return true


func has_ground(name: String) -> bool:
	return true
