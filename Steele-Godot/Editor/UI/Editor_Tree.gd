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


signal on_open(id: ResourceID)
