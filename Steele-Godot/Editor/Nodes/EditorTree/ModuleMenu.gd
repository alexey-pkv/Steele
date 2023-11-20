extends PopupMenu


var selected: TreeItem


func handle_index_pressed(index):
	if index == 3:
		open_in_os.emit(selected)
	elif index == 0:
		rename.emit(selected)
	elif index == 1:
		delete_module.emit(selected)


signal rename(item: TreeItem)
signal delete_module(item: TreeItem)
signal open_in_os(item: TreeItem)
