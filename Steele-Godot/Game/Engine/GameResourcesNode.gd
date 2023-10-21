extends Node
class_name GameResourcesNode


func is_floor(path: String) -> bool:
	const OPTIONS = [
		".floor.png",
		".floor.jpg",
		".floor.jpeg",
		".floor.svg",
		".floor.webp"
	]
	
	for o in OPTIONS:
		if path.ends_with(o):
			return true
	
	return false

func load_floor(path: String) -> void:
	pass


func load_file(path: String) -> void:
	if is_floor(path):
		load_floor(path)
	else:
		push_error("Unexpected file type for " + path)
