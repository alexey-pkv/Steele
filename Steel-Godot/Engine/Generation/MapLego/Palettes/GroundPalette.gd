class_name GroundPalette


var _palette:		Dictionary	= {}
var _totalWeight:	float		= 0


var palette: Dictionary:
	get:
		return _palette

var weight: float:
	get:
		return _totalWeight


func _calc_weight() -> void:
	_totalWeight = Arrays.sum_f(_palette.values())


func add(name: String, weight: float = 1.0) -> void:
	_palette[name] = weight
	_totalWeight += weight
	
	on_modified.emit()
	

func has(name: String) -> bool:
	return name in _palette

func remove(name: String) -> bool:
	if name not in _palette:
		return false
	
	_palette.erase(name)
	_totalWeight = Arrays.sum_f(_palette.values())
	
	on_modified.emit()
	
	return true

func generate(scope: GenerationScope) -> String:
	return scope.rng.next_weighted_dictionary(_palette, _totalWeight);


signal on_modified()

