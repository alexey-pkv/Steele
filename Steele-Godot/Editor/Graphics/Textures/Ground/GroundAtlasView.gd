extends Node2D
class_name GroundAtlasView


@export var padding: Vector2:
	get: return padding
	set(value):
		if value == padding:
			return
		
		padding = value
		_update()

var cell_size: Vector2:
	get:
		var data = DataRegistry.get_ground_atlas_id(atlas_id)
		
		if data == null:
			return Vector2.ZERO
		
		return data.cell_size

var rows: int:
	get:
		if atlas_id == null:
			return 0
		
		var data = DataRegistry.get_ground_atlas_id(atlas_id)
		
		if data == null:
			return 0
		
		return data.rows

var size: Vector2:
	get:
		var _rows		= rows
		var _cell_size	= cell_size
		var _padding	= padding
		
		if _rows <= 0:
			return Vector2.ZERO
		
		return Vector2(
			_cell_size.x * 4 + _padding.x * 3,
			_cell_size.y * _rows + _padding.y * (rows - 1)
		)

var atlas_id: ResourceID:
	get: return atlas_id
	set(value):
		if value != null:
			if !DataRegistry.textures_registry().has_ground_atlas(value.path):
				push_error("Atlas with ID " + value.path + " not found")
				return
		
		atlas_id = value
		_update()


func _clear() -> void:
	var i = 0
	var count = rows
	
	for child in get_children():
		if i >= count:
			remove_child(child)
			child.queue_free()
		

func _update_view(view: GroundTextureView, id: ResourceID, pos: Vector2) -> void:
	view.position	= pos
	view.cell_size	= cell_size
	view.ground_id	= id
	view.padding	= padding.x
	
	print(view.position)


func _add_view(id: ResourceID, pos: Vector2) -> void:
	var i = load("res://Editor/Graphics/Textures/Ground/GroundTextureView.tscn")
	var view = i.instantiate()
	
	add_child(view)
	_update_view(view, id, pos)


func _update():
	if !is_inside_tree() || atlas_id == null:
		_clear()
		return
	
	
	var children = get_children()
	var children_count = len(children)
	
	var offset = padding.y + cell_size.y
	var pos = cell_size / 2
	var id = atlas_id
	
	for i in range(rows):
		var child_id = id.create_child_i(i)
		
		if i < children_count:
			_update_view(children[i], child_id, pos)
		else:
			_add_view(child_id, pos)
		
		pos.y += offset
	
	_clear()
	queue_redraw()


func _enter_tree():
	_update()
