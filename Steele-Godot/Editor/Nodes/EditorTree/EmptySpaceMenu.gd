extends PopupMenu


var selected: TreeItem


func handle_id_pressed(id):
	if id == 0:
		create_new_module.emit()
	else:
		open_in_os.emit(null)


signal create_new_module
signal open_in_os(item: TreeItem)
