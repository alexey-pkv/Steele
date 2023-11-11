extends Control


var c_loading_scene: LoadingScene: 
	get: return $LoadingScene if is_inside_tree() else null

var c_resources: GameResourcesScene:
	get: return $Gamec_resources if is_inside_tree() else null

var c_main_view: Control:
	get: return $Main if is_inside_tree() else null


var me: Node2D:
	get: return $Main/Scene/Me


func _ready():
	c_main_view.visible = false
	c_loading_scene.visible = true
	
	c_loading_scene.begin()
	
	var loc = Isometric.grid_to_local(Vector3i(10, -1, 0), Vector3i(32, 16, 0))
	
	me.position = loc


func _process(delta):
	print(delta)


func handle_loading_scene_complete():
	c_main_view.visible = true
	c_loading_scene.queue_free()


func handle_map_patch_node_on_click(event: GridCellButtonArgs) -> void:
	print(event.at)
