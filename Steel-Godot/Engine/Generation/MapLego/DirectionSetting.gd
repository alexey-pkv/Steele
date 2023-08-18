class_name DirectionSetting


var is_any:		bool			= true
var variable:	String			= ""
var direction:	int				= -1
var directions:	Array[float]	= [1.0, 1.0, 1.0, 1.0]


func set_weight(dir: int, weight: float) -> void:
	direction = -1
	directions[dir / 2] = weight

func get_weight(dir: int) -> float:
	return directions[dir / 2]

func _from_variable(scope: GenerationScope) -> int:
	var val = scope.variables.get_var(variable)
	
	if val is DirectionSetting:
		return val.generate(scope)
	elif val is int:
		return val
	elif val is CellFill:
		return val.direction.generate(scope)
	
	scope.set_error("Failed to generate direction from variable '" + variable + "'")
	
	return 0

func generate(scope: GenerationScope) -> int:
	if variable != "":
		return _from_variable(scope)
	
	if is_any:
		return scope.rng.next_int_range(0, 3) * 2
	
	if direction >= 0:
		return direction
	
	var index = scope.rng.next_weighted_index(directions);
	
	return index * 2
