class_name Resources_Common


const RESOURCES_PATH = [
	"res://Resources/Editor/",
	"user://Resources/Editor/"
]



static func get_resource_path(path: String) -> String:
	for pref in RESOURCES_PATH:
		path = path.trim_prefix(pref)
		
	return path

