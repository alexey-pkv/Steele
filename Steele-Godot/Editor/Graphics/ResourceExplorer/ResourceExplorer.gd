@tool
extends Control
class_name ResourceExplorer


const FloorItemInstace = preload("res://Editor/Graphics/ResourceExplorer/Items/FloorItem.tscn")


var c_margin_container: MarginContainer:
	get:
		return $MarginContainer if is_inside_tree() else null

var c_main: GridContainer:
	get:
		return $MarginContainer/VBoxContainer/HFlowContainer if is_inside_tree() else null


@export var margin: float:
	get: return margin
	set(v):
		margin = v
		_update()

@export var spacing: Vector2i:
	get: return spacing
	set(v):
		spacing = v
		_update()

@export var cell_size: Vector2i:
	get: return cell_size
	set(v):
		cell_size = v
		_update()

var selected_id: ResourceID = null: 
	get: return selected_id


func _update_margin() -> void:
	var container = c_margin_container
	
	if container != null:
		container.add_theme_constant_override("margin_top",		margin)
		container.add_theme_constant_override("margin_left",	margin)
		container.add_theme_constant_override("margin_bottom",	margin)
		container.add_theme_constant_override("margin_right",	margin)

func _clear() -> void:
	if c_main == null:
		return
	
	selected_id = null
	
	for child in c_main.get_children():
		child.queue_free()

func _add_floot(resource_id: ResourceID) -> void:
	var item = FloorItemInstace.instantiate()
	var main = c_main
	
	if main == null:
		item.queue_free()
		return
	
	item.scale = Vector2(3, 3)
	item.resource_id = resource_id
	item.position = Vector2(32, 64)
	
	item.on_pressed.connect(_handle_item_pressed)
	
	main.add_child(item)


func _add_atlas(data: AtlasData) -> void:
	for id in data.get_child_ids():
		_add_floot(id)

func _update() -> void:
	_update_margin()
	_clear()
	
	var global = TemplatesRegistryNode.global()
	
	if global == null:
		return
	
	var registry = global.registry
	
	for key in registry:
		var item: AbstractRegistryObject = registry[key]
		
		if item.m_type == TemplateType.TYPE_GROUND_ATLAS:
			_add_atlas(item)
		

func _handle_item_pressed(id: ResourceID) -> void:
	for child in c_main.get_children():
		if id.equals(child.resource_id):
			child.select()
		else:
			child.deselect()
	
	selected_id = id
	
	on_selected.emit(selected_id)


func _ready():
	_update()


func update_items() -> void:
	_update()


signal on_selected(id: ResourceID)
