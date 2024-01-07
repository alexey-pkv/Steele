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

static func get_direction_vector_v3(v: Vector3) -> Vector3i:
	var dir = Vector3i.ZERO
	
	if v.x: dir.x = 1 if v.x > 0 else -1
	if v.y: dir.y = 1 if v.y > 0 else -1
	if v.z: dir.z = 1 if v.z > 0 else -1
	
	return dir

static func get_direction_vector_v3i(v: Vector3i) -> Vector3i:
	var dir = Vector3i.ZERO
	
	if v.x: dir.x = 1 if v.x > 0 else -1
	if v.y: dir.y = 1 if v.y > 0 else -1
	if v.z: dir.z = 1 if v.z > 0 else -1
	
	return dir

static func normalize_v3i(v: Vector3i) -> Vector3i:
	return v.clamp(-Vector3i.ONE, Vector3i.ONE)
	
static func normalize_v2i(v: Vector2i) -> Vector2i:
	return v.clamp(-Vector2i.ONE, Vector2i.ONE)
