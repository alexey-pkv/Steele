@tool
extends GridCellMotionArgs
class_name GridCellHoverArgs


@export var previous_v3: Vector3i:
	get: return previous_v3
	set(v): previous_v3 = v


var previous_v2: Vector2i:
	get: 
		var at3 = previous_v3
		return Vector2i(at3.x, at3.y)

