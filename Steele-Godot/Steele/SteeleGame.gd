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
	curr_pos = Vector2i(10, -1)
	
	me.position = loc


func _process(delta):
	if !should_move:
		return
	
	is_moving = true
	
	if next_pos == curr_pos:
		if curr_pos == target_pos:
			should_move = false
			is_moving = false
			return
		
		calc_next()
	
	var coord_curr = me.position
	var coord_diff = next_coord - coord_curr
	var change = curr_speed * delta
	
	if coord_diff.length() <= change.length():
		me.position = next_coord
		curr_pos = next_pos
	else:
		me.position += change


func handle_loading_scene_complete():
	c_main_view.visible = true
	c_loading_scene.queue_free()


var speed: float = 0.2
var curr_speed: Vector2
var curr_pos: Vector2i
var target_pos: Vector2i
var next_pos: Vector2i
var next_coord: Vector2

var is_moving = false
var should_move = false


func calc_next() -> void:
	if curr_pos == target_pos:
		return
	
	var diff = target_pos - curr_pos
	var abs_diff = abs(diff)
	
	if abs_diff.x == abs_diff.y:
		diff = diff / abs_diff.x
	elif abs_diff.x < abs_diff.y:
		diff.y = diff.y / abs_diff.y
		diff.x = 0
	else:
		diff.y = 0
		diff.x = diff.x / abs_diff.x
	
	next_pos = curr_pos + diff
	next_coord = Isometric.grid_to_local(Vector3i(next_pos.x, next_pos.y, 0), Vector3i(32, 16, 0))
	
	var curr_coord = Vector2(Isometric.grid_to_local(Vector3i(curr_pos.x, curr_pos.y, 0), Vector3i(32, 16, 0)))
	curr_speed = (next_coord - curr_coord) / speed


func handle_map_patch_node_on_click(event: GridCellButtonArgs) -> void:
	if event.mouse_event.pressed:
		target_pos = event.at
		should_move = true
		
		if !is_moving:
			calc_next()
