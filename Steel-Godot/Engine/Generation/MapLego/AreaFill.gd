class_name AreaFill


var _cells: Dictionary		= {}

var name: String


func _init(_name: String):
	name = _name


func get_cells() -> Dictionary:
	return _cells

func has_cell_at(at: Vector2i) -> bool:
	return at in _cells

func get_cell(at: Vector2i) -> CellFill:
	if not has_cell_at(at):
		return null
	
	return _cells[at]

func set_cell(at: Vector2i, cell_fill: CellFill) -> void:
	_cells[at] = cell_fill


func generate(scope: GenerationScope) -> Dictionary:
	var res := {}
	
	scope.push_gen_stack("Fill " + name)
	
	for at in _cells:
		var fill: CellFill = _cells[at]
		
		scope.push_gen_stack("Fill at " + str(at))
		
		res[at] = fill.generate(scope)
		
		if not scope.pop_gen_stack():
			return {}
	
	scope.pop_gen_stack()
	
	return res
	
