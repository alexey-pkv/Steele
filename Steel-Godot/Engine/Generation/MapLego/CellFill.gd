class_name CellFill


var variable:	String				= ""
var direction:	DirectionSetting	= DirectionSetting.new()
var ground:		String				= ""
var palette:	Palette				= null


func _name_from_variable(scope: GenerationScope) -> String:
	var val = scope.variables.get_var(variable)
	
	if val is String:
		if !scope.has_ground(val):
			scope.set_error("A ground named '" + val +
			 " from variable '" + variable + "' does not exists")
		
		return val
	elif val is GroundPalette:
		return val.generate(scope)
	elif val is Palette:
		return val.ground_palette.generate(scope)
	
	scope.set_error("Failed to generate ground texture name from variable '" + variable + "'")
	
	return ""


func generate(scope: GenerationScope) -> GroundData:
	if variable != "":
		var val = scope.variables.get_var(variable)
		
		if val is CellFill:
			return val.generate(scope)
	
	var dir	:= direction.generate(scope)
	var name: String
	
	if !scope.continue_generation:
		return null
	
	if ground != "":
		name = ground
	elif palette != null:
		name = palette.ground_palette.generate(scope)
	else:
		name = _name_from_variable(scope)
	
	if !scope.continue_generation:
		return null
	
	return GroundData.new(ground, dir)
		
