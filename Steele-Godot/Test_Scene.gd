extends Control





func _ready():
	
	pass
	
	
	

var lastrow = 0

func _input(_event):
	if Input.is_action_pressed("ui_cancel"):
		_show_main_menu()
	
	var _id = ResourceID.cast("res://Resources/TestResources/Ground/marble.32x16.tile-set.png")
	# $GroundAtlasView.atlas_id = id


func _notification(what):
	if what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_IN:
		pass
	elif what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_OUT:
		pass

func _show_main_menu():	
	get_tree().change_scene_to_file("res://Components/UI/MainMenu/MainMenu.tscn")

