@tool
extends Node2D
class_name AreaSelect


const SCENE_CellSelect = preload("res://Game/Graphics/Components/Cell/CellSelect.tscn")


func _get_configuration_warnings():
	if is_inside_tree() && get_child_count() == 0:
		return ["Scene incorrectly imported"]
	
	return []


var m_area: Area = Area.new()


var area: Area:
	get: return m_area

var is_empty: bool:
	get: return m_area.is_empty()

var c_grid: IsometricGrid:
	get: return $Grid if is_inside_tree() else null

var c_name: Label:
	get: return $Name if is_inside_tree() else null


@export var border_color: Color:
	get: return border_color
	set(c): 
		if border_color != c:
			border_color = c
			_update()

@export var fill_color: Color:
	get: return fill_color
	set(c): 
		if fill_color != c:
			fill_color = c
			_update()

@export var cell_size: Vector2i:
	get: return cell_size
	set(v): 
		if cell_size != v:
			cell_size = v
			_update()

@export var border_width: float:
	get: return border_width
	set(w): 
		if border_width != w:
			border_width = w
			_update()

@export var text: String:
	get: return text
	set(t):
		if text != t:
			text = t
			_update_text()

@export var text_theme: Theme:
	get: return text_theme
	set(t):
		if text_theme != t:
			text_theme = t
			_update_text()

@export var text_color: Color:
	get: return text_color
	set(t):
		if text_color != t:
			text_color = t
			_update_text()


var name_label: Label: 
	get: return $Name


func _get_cell() -> CellSelect:
	var c = SCENE_CellSelect.instantiate()
	_init_cell(c)
	return c

func _init_cell(c: CellSelect) -> void:
	c.fill_color	= fill_color
	c.border_color	= border_color
	c.border_width	= border_width
	c.cell_size		= cell_size

func _update() -> void:
	if !is_inside_tree():
		return
	
	c_grid.size = Vector3i(cell_size.x, cell_size.y, 0)
	
	var fc = fill_color
	var bc = border_color
	
	for c in c_grid.get_children():
		_init_cell(c)
	
	for v in m_area.points():
		add_v2i(v)

func _update_text() -> void:
	if !is_inside_tree():
		return
	
	if text == "" || is_empty:
		c_name.visible = false
		return
	
	c_name.visible = true
	c_name.text = text
	c_name.theme = text_theme
	c_name.modulate = text_color
	
	var left_bottom = Vector2i(m_area.left(), m_area.bottom())
	var right_top = Vector2i(m_area.right(), m_area.top())
	
	var pos_left_bottom = c_grid.grid_to_local(left_bottom)
	var pos_right_top = c_grid.grid_to_local(right_top)
	
	var pos = (pos_left_bottom + pos_right_top) / 2
	var _size = c_name.size
	
	_size.x *= c_name.scale.x
	_size.y *= c_name.scale.y
	
	pos -= _size / 2
	
	c_name.position = pos
	

func _ready():
	_update()
	_update_text()

func _exit_tree():
	var grid = c_grid
	
	if grid != null:
		grid.clear()


func has_v2i(v: Vector2i) -> bool:
	return m_area.contains_v2i(v)


func add_r2i(v: Rect2i) -> void:
	for x in v.size.x:
		for y in v.size.y:
			add_v2i(v.position + Vector2i(x, y))

func add_v2i(v: Vector2i) -> void:
	var was_empty = is_empty
	
	m_area.combine_v2i(v)
	
	if !is_inside_tree():
		return
	
	_update_text.call_deferred()
	
	if c_grid.has_z0(v.x, v.y):
		return
	
	c_grid.set_at_z0(v.x, v.y, _get_cell())

func remove_v2i(v: Vector2i) -> void:
	m_area.subtract_v2i(v)
	
	if !is_inside_tree():
		return
	
	c_grid.remove_z0(v.x, v.y)

func remove_v2ia(va: Array[Vector2i]) -> void:
	for v in va:
		remove_v2i(v)

func add_v2ia(va: Array[Vector2i]) -> void:
	for v in va:
		add_v2i(v)
