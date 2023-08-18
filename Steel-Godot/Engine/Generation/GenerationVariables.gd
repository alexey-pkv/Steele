class_name GenerationVariables


var _variables: Dictionary = {}


func push(name: String, value) -> void:
	if name in _variables:
		var values: Array = _variables[name]
		values.append(value)
	else:
		_variables[name] = [value]

func pop(name: String) -> void:
	if name not in _variables:
		return
	
	var values: Array = _variables[name]
	
	if len(values) <= 1:
		_variables.erase(name)
	else:
		values.pop_back()

func get_var(name: String):
	if name not in _variables:
		return null
	
	return _variables[name][-1]
