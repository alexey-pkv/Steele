extends Tree
class_name Editor_Tree


@onready var m_popups = [
	$FolderMenu,
	$EmptySpaceMenu,
	$ItemMenu,
	$ModuleMenu
]


static func get_metadata(item: TreeItem) -> TreeItemMetadata:
	return item.get_metadata(0) if item != null else null

static func get_or_create(p_root: TreeItem, text: String) -> TreeItem:
	for c in p_root.get_children():
		if c.get_text(0) == text:
			return c
	
	var metadata = TreeItemMetadata.create_from_folder(get_metadata(p_root), text)
	var child = p_root.create_child()
	
	child.set_metadata(0, metadata)
	child.set_editable(0, false)
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
		return selected != null && Editor_Tree.get_metadata(selected).is_resource

var selected_id: int: 
	get:
		var selected = get_selected()
		return Editor_Tree.get_metadata(selected).resource_id if selected != null else SteeleID.NULL_ID

var root: TreeItem: 
	get:
		if root == null:
			root = create_item()
		
		return root

func get_selected_metadata() -> TreeItemMetadata:
	return Editor_Tree.get_metadata(get_selected())

func _open_popup(t: PopupMenu, at: Vector2) -> void:
	var item = get_item_at_position(at)
	
	for p in m_popups:
		if p == t:
			p.selected = item
			p.position = at
			p.show()
		else:
			p.selected = null
			p.hide()
	
	if item != null:
		set_selected(item, 0)

func _handle_item_menu(item: TreeItem, at: Vector2) -> void:
	if item == null:
		_open_popup($EmptySpaceMenu, at)
		return
	
	var metadata = Editor_Tree.get_metadata(item)
		
	if metadata.is_module:
		_open_popup($ModuleMenu, at)
	elif metadata.is_folder:
		_open_popup($FolderMenu, at)
	else:
		_open_popup($ItemMenu, at)

func find_temp_name() -> String:
	var new_name: String
	var index = 0
	var exists = true
	
	while exists:
		exists = false
		index = index + 1
		new_name = "Module " + str(index)
		
		for child in root.get_children():
			if child.get_text(0) == new_name:
				exists = true
				break
	
	return new_name

func add_resource(id: int) -> void:
	var resource = Resources.get_id(id)
	var parts = resource.get_path_parts()
	var item = Editor_Tree.get_or_create_path(root, parts)
	var metadata = TreeItemMetadata.create_from_resource(resource)
	
	item.set_editable(0, false)
	item.set_metadata(0, metadata)
	item.set_cell_mode(1, TreeItem.CELL_MODE_CUSTOM)
	
func remove_resource(_id: int) -> void:
	pass
	
func is_valid_name(item: TreeItem) -> bool:
	var item_name = item.get_text(0)
	
	for sybling in item.get_parent().get_children():
		if sybling != item && sybling.get_text(0) == item_name:
			return false
	
	return true


func handle_item_activated():
	if !is_selected:
		return
	
	on_open.emit(selected_id)

func handle_gui_input(event):
	if !(event is InputEventMouseButton):
		return
	if event.button_index != 2:
		return
	if !event.pressed:
		return
	
	var item = get_item_at_position(event.position)
	
	_handle_item_menu(item, event.position)


func handle_create_new_module():
	var temp_name = find_temp_name()
	var item = Editor_Tree.get_or_create(root, temp_name)
	
	set_selected(item, 0)
	edit_selected.call_deferred(true)

func handle_item_edited():
	var item: TreeItem = get_selected()
	var new_name = item.get_text(0)
	var metadata = Editor_Tree.get_metadata(item)
	
	if new_name == metadata.item_name:
		return
	
	if !is_valid_name(item):
		item.set_text(0, metadata.item_name)
		return
	
	var original_path = metadata.relative_path
	
	if metadata.rename(new_name) != OK:
		item.set_text(0, metadata.item_name)
		return
	
	if metadata.is_resource:
		# TODO: rename resource
		pass
	
	$ChangeNode.rename(original_path, metadata.relative_path)


func handle_open_in_os(item: TreeItem):
	var metadata = Editor_Tree.get_metadata(item)
	var path
	
	if metadata != null:
		path = metadata.full_path
		
		if metadata.is_folder:
			path += "/"
	else:
		path = OS.get_user_data_dir() + "/assets/"
	
	OS.shell_show_in_file_manager(path)


func handle_delete(_item: TreeItem):
	pass # Replace with function body.

func handle_rename(item: TreeItem):
	if item != null:
		set_selected(item, 0)
		edit_selected.call_deferred(true)


signal on_open(id: int)
