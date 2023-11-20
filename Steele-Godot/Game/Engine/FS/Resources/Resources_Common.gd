class_name Resources_Common


const RESOURCES_PATH = [
	"user://assets"
]


static func get_resource_path(path: String) -> String:
	for pref in RESOURCES_PATH:
		path = path.trim_prefix(pref + "/")
		
	return path

