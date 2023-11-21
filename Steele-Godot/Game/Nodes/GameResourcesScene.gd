extends Node
class_name GameResourcesScene


func load_file(path: String) -> void:
	var id: int = SteeleID.NULL_ID
	
	if Loader_Floor.is_floor(path):
		id = Loader_Floor.load_floor(path)
	else:
		push_error("Unexpected file type for " + path)
		return 
	
	if id != SteeleID.NULL_ID:
		on_resource_loaded.emit(id)
	else:
		on_failed_to_load.emit(path)


signal on_failed_to_load(path: String)
signal on_resource_loaded(id: int)
