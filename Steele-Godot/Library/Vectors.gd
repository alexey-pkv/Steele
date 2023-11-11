@tool
class_name Vectors


static func get_line(start: Vector2i, end: Vector2i) -> Array:
	var diff = Vector2(end - start)
	var max_dim = max(abs(diff.x), abs(diff.y))
	var step = diff / max_dim
	var curr = Vector2(start)
	var res  = []
	
	for i in max_dim + 1:
		res.push_back(Vector2i(curr.round()))
		curr += step
	
	return res
