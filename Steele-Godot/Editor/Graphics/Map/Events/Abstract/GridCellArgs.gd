@tool
extends Resource
class_name GridCellArgs


@export var at_v3: Vector3i:
	get: return at_v3
	set(v): at_v3 = v


var at_v2: Vector2i:
	get: 
		var at3 = at_v3
		return Vector2i(at3.x, at3.y)
