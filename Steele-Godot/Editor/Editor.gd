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

var c_editor_tabs: Editor_Tabs:
	get: return $GridContainer/VBoxContainer/EditorTabs

var c_resource_explorer: ResourceExplorer:
	get: return $GridContainer/SettingsContainer/TabContainer/ResourceExplorer


func _ready():
	c_main_view.visible = false
	
	c_loading_scene.visible = true
	c_loading_scene.begin()


func _on_loading_scene_complete():
	c_main_view.visible = true
	c_loading_scene.queue_free()
	c_resource_explorer.update_items()

func _on_game_resources_failed(path: String) -> void:
	print("Failed to load: " + path)

func _on_game_resources_loaded(id: ResourceID) -> void:
	c_tree.add_resource(id)

func _on_explorer_open(id):
	c_editor_tabs.open_resource(id)
