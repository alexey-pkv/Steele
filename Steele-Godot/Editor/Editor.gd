extends Control
class_name EditorScene


var c_loading_scene: LoadingScene: 
	get: return $LoadingScene

var c_resources: GameResourcesScene:
	get: return $Gamec_resources

var c_main_view: Control:
	get: return $GridContainer

var c_tree: Editor_Tree:
	get: return $GridContainer/ExplorerContainer/Explorer


func _ready():
	c_main_view.visible = false
	
	c_loading_scene.visible = true
	c_loading_scene.begin()


func _on_loading_scene_complete():
	c_main_view.visible = true
	c_loading_scene.queue_free()

func _on_game_resources_failed(path: String) -> void:
	print("Failed to load: " + path)

func _on_game_resources_loaded(id: ResourceID) -> void:
	c_tree.add_resource(id)
