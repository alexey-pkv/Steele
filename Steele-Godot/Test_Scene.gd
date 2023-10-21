extends Control





func _ready():
	$LoadingScene.begin()
	return
	var map = IDMap.add("abasd")
	
	
	print(IDMap.get_id("abasd"))
	print(IDMap.get_id("aqsasd"))
	print(IDMap.get_name(map))
	print(map)
	
	var res = "res://Resources/TestResources/Ground/marble.32x16.tile-set.png"
	var r = load(res)
	
	
	var id = TextureRegistry.add_ground_textures(r, res, 5)
	var g_id = id.create_child_i(2)
	
	var data = AtlasData.create_gound_atlas(id)
	
	data.cell_size = Vector2(32, 16)
	data.rows = 5
	
	DataRegistry.textures_registry().add_atlas(data)
	
	

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
