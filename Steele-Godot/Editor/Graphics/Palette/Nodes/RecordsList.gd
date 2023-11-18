extends Control
class_name RecordsList


const SCENE_PaletteRecord = preload("res://Editor/Graphics/Palette/Nodes/PaletteRecord.tscn")


var m_resources: Dictionary = {}


func add_resource(id: int, weight: int) -> void:
	if m_resources.has(id):
		return
	
	m_resources[id] = [id, weight]
	
	var record: PaletteRecord = SCENE_PaletteRecord.instantiate()
	
	record.resource_id = id
	record.resource_weight = weight
	record.on_weight_changed.connect(handle_weight_changed)
	
	# record.mouse_entered.connect(func():
	#	handle_palette_mouse_entered(id))
	
	if is_inside_tree():
		$Container.add_child(record)

func toggle_resource(id: int) -> void:
	for c in $Container.get_children():
		var r: PaletteRecord = c
		
		if r.resource_id == id:
			c.queue_free()
			m_resources.erase(id)
			return
	
	add_resource(id, 1)

func handle_weight_changed(id: int, weight: int) -> void:
	if m_resources.has(id):
		return
	
	m_resources[id] = [
		m_resources[id][0],
		weight
	]
	
	on_weight_changed.emit(id, weight)


func handle_palette_mouse_entered(id: int):
	for c in $Container.get_children():
		var r: PaletteRecord = c
		
		if r.resource_id == id:
			r.preview_mode = 1
		else:
			r.preview_mode = 0


signal on_weight_changed(id: int, weight: int)



