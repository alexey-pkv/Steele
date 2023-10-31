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
	var rng: RNGNode = c_rng
	
	var a =  ""
	
	var s = rng.m_rng.get_state()
	
	for i in range(100):
		var n = rng.next_int_r(0, 9)
		a += str(n)
	
	print(a)
	a = ""
	
	rng.m_rng.set_state(s)
	
	for i in range(100):
		var n = rng.next_int_r(0, 9)
		a += str(n)
	
	print(a)
	a = ""
	

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





func _on_map_editor_on_hover(args: GridCellHoverArgs):
	# print("Hovered " + str(args.at_v2) + " p " + str(args.previous_v2))
	pass # Replace with function body.


func _on_map_editor_on_mouse_button(args: GridCellButtonArgs):
	# print("Pressed")
	pass # Replace with function body.

