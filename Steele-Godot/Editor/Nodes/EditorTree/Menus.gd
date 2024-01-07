extends Node


func handle_index_pressed(index, selected: TreeItem):
	# General
	if index == 1000:
		on_open_in_os.emit(selected)
	
	# FS Actions
	elif index == 0:
		on_rename.emit(selected)
	elif index == 1:
		on_delete.emit(selected)
		
	# Modules
	elif index == 100:
		on_delete_module.emit(selected)
	elif index == 101:
		on_create_new_module.emit()


signal on_create_new_module
signal on_delete(item: TreeItem)
signal on_rename(item: TreeItem)
signal on_delete_module(item: TreeItem)
signal on_open_in_os(item: TreeItem)
