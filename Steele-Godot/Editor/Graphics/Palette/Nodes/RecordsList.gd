extends Control
class_name RecordsList


const SCENE_PaletteRecord = preload("res://Editor/Graphics/Palette/Nodes/PaletteRecord.tscn")


var m_resources: Dictionary = {}


func add_resource(id: ResourceID, weight: int) -> void:
	if m_resources.has(id.registry_id):
		return
	
	m_resources[id.registry_id] = [id.registry_id, weight]
	
	var record: PaletteRecord = SCENE_PaletteRecord.instantiate()
	
	record.resource_id = id
	record.resource_weight = weight
	record.on_weight_changed.connect(handle_weight_changed)
	
	# record.mouse_entered.connect(func():
	#	handle_palette_mouse_entered(id))
	
	if is_inside_tree():
		$Container.add_child(record)

func toggle_resource(id: ResourceID) -> void:
	for c in $Container.get_children():
		var r: PaletteRecord = c
		
		if r.resource_id.equals(id):
			c.queue_free()
			m_resources.erase(id.registry_id)
			return
	
	add_resource(id, 1)

func handle_weight_changed(id: ResourceID, weight: int) -> void:
	if m_resources.has(id.registry_id):
		return
	
	m_resources[id.registry_id] = [
		m_resources[id.registry_id][0],
		weight
	]
	
	on_weight_changed.emit(id, weight)


func handle_palette_mouse_entered(id: ResourceID):
	for c in $Container.get_children():
		var r: PaletteRecord = c
		
		if r.resource_id.equals(id):
			r.preview_mode = 1
		else:
			r.preview_mode = 0


signal on_weight_changed(id: ResourceID, weight: int)



