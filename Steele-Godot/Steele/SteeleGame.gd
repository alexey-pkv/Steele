extends Control


var c_loading_scene: LoadingScene: 
	get: return $LoadingScene if is_inside_tree() else null

var c_resources: GameResourcesScene:
	get: return $Gamec_resources if is_inside_tree() else null

var c_main_view: Control:
	get: return $Main if is_inside_tree() else null


func _ready():
	c_main_view.visible = false
	c_loading_scene.visible = true
	
	c_loading_scene.begin()


func handle_loading_scene_complete():
	c_main_view.visible = true
	c_loading_scene.queue_free()


func handle_map_patch_node_on_click(event):
	pass # Replace with function body.
