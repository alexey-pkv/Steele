@tool
extends Control
class_name PaletteRecord


const SCENE_GroundSprite2D = preload("res://Game/Graphics/World/Map/Cell/GroundSprite2D.gd")


var m_update_pending: bool = false
var m_direction = Direction.NORTH


var c_preview_timer: Timer:
	get: return $PreviewTimer if is_inside_tree() else null

var c_preview_node: Node2D:
	get: return $HBoxContainer/margin_preview/node_preview if is_inside_tree() else null


var resource_id: ResourceID:
	get: return resource_id
	set(n): 
		resource_id = n
		
		if n == null:
			unset_preview()
			
			resource_name = ""
			resource_path = ""
		else:
			resource_name = n.short_name
			resource_path = n.path


@export var preview_mode: int = 0:
	get: return preview_mode
	set(m): 
		if preview_mode == m:
			return
			
		preview_mode = m
		_update_preview_mode()

@export var resource_name: String:
	get: return resource_name
	set(n): 
		if resource_name == n: 
			return
		
		resource_name = n
		_queue_update()

@export var resource_path: String:
	get: return resource_path
	set(n): 
		if resource_path == n: 
			return
			
		resource_path = n
		_queue_update()

@export var resource_weight: int:
	get: return resource_weight
	set(v): 
		if resource_weight == v: 
			return
		
		resource_weight = v
		_queue_update()


func _get_configuration_warnings():
	var notes = []
	
	if is_inside_tree() && get_child_count() == 0:
		notes.push_back("Scene incorrectly imported")
	
	return notes


func _update_preview_mode() -> void:
	if !is_inside_tree():
		return
	
	if preview_mode == 0:
		c_preview_timer.stop()
	else:
		c_preview_timer.start()

func _queue_update() -> void:
	if m_update_pending: 
		return
	
	m_update_pending = true
	_update.call_deferred()

func _update_preview() -> void:
	var data = TemplatesRegistryNode.global().get_data(resource_id)
	
	if data != null || !resource_id.is_child:
		return
	
	data = TemplatesRegistryNode.global().get_data(resource_id.get_parent())
	
	if data == null:
		return
	
	if data.type == TemplateType.TYPE_GROUND_ATLAS:
		var node = SCENE_GroundSprite2D.new()
		
		node.scale = Vector2(3, 3)
		node.ground_id = resource_id
		
		set_preview(node)

func _update() -> void:
	m_update_pending = false
	
	if !is_inside_tree():
		return
	
	$HBoxContainer/margin_name/vbox/Name.text = resource_name
	$HBoxContainer/margin_name/vbox/Path.text = resource_path
	
	var curr_weight_text = $HBoxContainer/margin_weight/Weight.text
	
	if resource_weight == 1:
		if $HBoxContainer/margin_weight/Weight != get_viewport().gui_get_focus_owner():
			$HBoxContainer/margin_weight/Weight.text = str(resource_weight)
		elif curr_weight_text != "" && curr_weight_text != "1":
			$HBoxContainer/margin_weight/Weight.text = str(resource_weight)
	elif str(resource_weight) != curr_weight_text:
		$HBoxContainer/margin_weight/Weight.text = str(resource_weight)
	
	if resource_id == null:
		unset_preview()
	else:
		_update_preview()


func _ready():
	if !is_inside_tree():
		return
	
	_queue_update()
	_update_preview_mode.call_deferred()
	
func preview_node() -> Node2D:
	var node = c_preview_node
	
	if node == null || node.get_child_count() == 0:
		return null

	return node.get_child(0)

func unset_preview() -> void:
	var node = c_preview_node
	
	if node == null || node.get_child_count() == 0:
		return
	
	for child in node.get_children():
		child.queue_free()
	
func set_preview(target: Node2D) -> void:
	var node = c_preview_node
	
	if node == null: 
		return
	
	for child in node.get_children():
		child.queue_free()
	
	node.add_child(target)


func _on_weight_text_changed(new_text):
	var value = int(new_text)
	value = clamp(value, 1, 1000000)
	resource_weight = value
	
	if str(value) != new_text:
		if value != 1 || (new_text != "" && new_text != "1"):
			var caret_at = $HBoxContainer/margin_weight/Weight.caret_column
			$HBoxContainer/margin_weight/Weight.text = str(value)
			$HBoxContainer/margin_weight/Weight.caret_column = caret_at - 1
	
	on_weight_changed.emit(resource_id, resource_weight)


func handle_preview_timer_timeout() -> void:
	if resource_id == null:
		return
	
	var node = preview_node()
	
	if node == null: 
		return
	
	if node is GroundSprite2D:
		m_direction = Direction.rotate_clockwise(m_direction)
		node.direction = m_direction

func handle_weight_focus_exited():
	if $HBoxContainer/margin_weight/Weight.text == "":
		$HBoxContainer/margin_weight/Weight.text = str(resource_weight)


signal on_weight_changed(id: ResourceID, weight: int)
