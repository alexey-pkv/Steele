@tool
extends Resource
class_name GridCellArgs


@export var at_v3: Vector3i:
	get: return at_v3
	set(v): at_v3 = v

@export var is_empty: bool:
	get: return is_empty
	set(b): is_empty = b


var at_v2: Vector2i:
	get: 
		var at3 = at_v3
		return Vector2i(at3.x, at3.y)
