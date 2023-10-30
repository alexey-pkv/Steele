extends Control


var c_map: IsometricGrid:
	get: return $IsometricGrid


var d = {
	"A": 1,
	"B": 2,
	"C": 3
}

var k


func _ready():
	for i in range(100_000):
		d[i] = i
	
	print("done" )
	k = d.keys()
	print("done keys")
	
	

var lastrow = 0
var lastnoe = null

func _input(_event):
	if Input.is_action_pressed("ui_cancel"):
		_show_main_menu()
	
	var _id = ResourceID.cast("res://Resources/TestResources/Ground/marble.32x16.tile-set.png")
	# $GroundAtlasView.atlas_id = id
	
	if _event is InputEventMouseMotion:
		var ind = c_map.global_to_grid(_event.position)
		var node = c_map.get_at_v2i(ind)
		
		if lastnoe != null && lastnoe != node:
			lastnoe.texture = $IsometricGrid/Sprite2D.texture
		
		if node != null:
			node.texture = $IsometricGrid/Sprite2D2.texture
		
		lastnoe = node


func _notification(what):
	if what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_IN:
		pass
	elif what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_OUT:
		pass

func _show_main_menu():	
	get_tree().change_scene_to_file("res://Components/UI/MainMenu/MainMenu.tscn")



