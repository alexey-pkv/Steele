extends Control


var c_map: IsometricGrid:
	get: return $IsometricGrid


var d = {
	"A": 1,
	"B": 2,
	"C": 3
}

var k

var c_rng: RNGNode:
	get: return $RNGNode


func _ready():
	
	
	var root: TreeItem = $Tree.create_item(null)
	root.set_text(0, "root ")
	
	for a in range(10):
		var i: TreeItem = $Tree.create_item(root)
		i.set_text(0, "hell world " + str(a))
	
	

var lastrow = 0
var lastnoe = null

func _input(_event):
	pass


func _notification(what):
	if what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_IN:
		pass
	elif what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_OUT:
		pass

func _show_main_menu():	
	get_tree().change_scene_to_file("res://Components/UI/MainMenu/MainMenu.tscn")





func _on_map_editor_on_hover(args: GridCellMotionArgs):
	# print("Hovered " + str(args.at_v2) + " p " + str(args.previous_v2))
	pass # Replace with function body.


func _on_map_editor_on_mouse_button(args: GridCellButtonArgs):
	
	# print("Pressed")
	pass # Replace with function body.



func _on_tree_custom_popup_edited(arrow_clicked):
	pass


func _on_tree_gui_input(event):
	# print($Tree.get_item_at_position(event.position))
	pass


func _on_grid_mouse_events_node_on_click(event: GridCellButtonArgs):
	pass



func _on_grid_mouse_events_node_on_hover(event: GridCellMotionArgs):
	pass

