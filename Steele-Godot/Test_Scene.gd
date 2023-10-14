extends Control






var _world_data: WorldData = null

var explorer: TextureExplorer:
	get:
		return $MarginContainer/Panel/MarginContainer/TextureExplorer

var dict = []


func _ready():
	var t: GroundTextures = TileSetLoader.load(
		"res://Resources/TestResources/Ground/marble.32x16.tile-set.png")
	
	var c = DoableStack.global()
	
	var aaa = ProjectSettings.globalize_path("res://Resources/TestResources/Ground/marble.32x16.tile-set.png")
	
	print(aaa);
	return;
	print(get_viewport().size);
	
	get_viewport().size = Vector2i(1200, 1200)
	
	var d = GroundTile.new()
	var g = Ground.new()
	var a = Area.ONE()
	
	var a2 = Area.ONE()
	
	a.add_offset(1, 1)
	a2.set_offset(4,4)
	a.combine_a(a2)
	
	
	print(a.debug_info())
	
	
	d.tile = 234
	d.index = 78
	g.add_tile(d)
	
	d.tile = 11
	d.index = 412
	g.add_tile(d)
	
	var n = g.tiles()
	
	for tile in n:
		print(tile.index)
	
	

func _input(event):
	if Input.is_action_pressed("ui_cancel"):
		_show_main_menu()
		
	#if event is InputEventKey and event.pressed:
	#	_world_data.roate_clockwise()
		
		
func _notification(what):
	if what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_IN:
		print("focus in")
	elif what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_OUT:
		print("focus out")

func _show_main_menu():	
	get_tree().change_scene_to_file("res://Components/UI/MainMenu/MainMenu.tscn")
