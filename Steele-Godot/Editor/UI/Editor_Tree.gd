extends Tree
class_name Editor_Tree


static func get_or_create(p_root: TreeItem, text: String) -> TreeItem:
	for c in p_root.get_children():
		if c.get_text(0) == text:
			return c
	
	var child = p_root.create_child()
	
	child.set_text(0, text)
	
	return child
	
static func get_or_create_path(p_root: TreeItem, path: Array) -> TreeItem:
	var curr_item = p_root
	
	for part in path:
		curr_item = get_or_create(curr_item, part)
	
	return curr_item


var is_selected: bool: 
	get:
		var selected = get_selected()
		return selected != null && selected.get_metadata(0) != null

var selected_id: ResourceID: 
	get:
		var selected = get_selected()
		return selected.get_metadata(0) if selected != null else null

var root: TreeItem: 
	get:
		if root == null:
			root = create_item()
		
		return root


func add_resource(id: ResourceID) -> void:
	var parts = id.get_path_parts()
	var item = Editor_Tree.get_or_create_path(root, parts)
	
	item.set_metadata(0, id)
	

func remove_resource(id: ResourceID) -> void:
	pass

func move_resource(prev: ResourceID, new: ResourceID) -> void:
	remove_resource(prev)
	add_resource(new)


func _on_item_activated():
	if !is_selected:
		return
	
	on_open.emit(selected_id)
	


signal on_open(id: ResourceID)


func _on_gui_input(event):
	if event is InputEventMouseButton:
		pass
