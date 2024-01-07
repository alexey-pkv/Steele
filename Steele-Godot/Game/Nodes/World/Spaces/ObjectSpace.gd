extends Node2D
class_name ObjectSpace


var sub_spaces:		Dictionary = {}
var is_visiable:	Dictionary = {}


func create_at(index: Vector3i) -> ObjectSubSpace:
	var n = ObjectSubSpace.new(index)
	
	if !(index in is_visiable):
		is_visiable[index] = false
	
	n.index = index
	n.visible = is_visiable[n]
	
	sub_spaces[index] = n
	add_child(n)
	
	return n

func get_at_or_create(index: Vector3i) -> ObjectSubSpace:
	if !(index in sub_spaces):
		return create_at(index)
	else:
		return sub_spaces[index]

func get_at(index: Vector3i) -> ObjectSubSpace:
	return sub_spaces[index] if index in sub_spaces else null

func set_visiability(index: Vector3i, visiable: bool) -> void:
	is_visiable[index] = visiable
	
	if index in is_visiable:
		var s: ObjectSubSpace = is_visiable[index]
		s.visible = visiable

func remove(index: Vector3i) -> bool:
	var n = get_at(index)
	
	is_visiable.erase(index)
	sub_spaces.erase(index)
	
	if n == null:
		return false
	
	n.queue_free()
	
	return true

func add_object(o: Node2D, index: Vector3i) -> void:
	var n = get_at_or_create(index)
	
	n.add_child(o)

func add_object_cell(o: Node2D, cell_index: Vector3i) -> void:
	add_object(o, Game.get_chunk_index(cell_index))

func move_object(o: Node2D, from: Vector3i, to: Vector3i) -> void:
	var f = get_at(from)
	var t = get_at_or_create(to)
	
	if f != null:
		f.remove_child(o)
	
	t.add_child(o)


func move_object_cells(o: Node2D, from: Vector3i, to: Vector3i) -> void:
	var chunk_from	= Game.get_chunk_index(from)
	var chunk_to	= Game.get_chunk_index(to)
	
	if chunk_from != chunk_to:
		move_object(o, chunk_from, chunk_to)
