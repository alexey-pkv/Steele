extends PopupMenu
class_name EditorPopupMenu


var selected: TreeItem


func handle_index_pressed(index):
	on_selected.emit(index, selected)


signal on_selected(index: int, item: TreeItem)
