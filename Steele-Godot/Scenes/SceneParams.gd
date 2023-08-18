extends Node


var _params = null


func set_params(params) -> void:
	_params = params

func get_params(key = null):
	if key != null:
		return _params[key]
	
	return _params
