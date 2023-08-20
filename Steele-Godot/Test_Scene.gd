extends Control


var _world_data: WorldData = null

var explorer: TextureExplorer:
	get:
		return $MarginContainer/Panel/MarginContainer/TextureExplorer

var dict = []


func _ready():
	var t: GroundTextures = TileSetLoader.load(
		"res://Resources/TestResources/Ground/marble.32x16.tile-set.png")
	
	print(get_viewport().size);
	
	get_viewport().size = Vector2i(1200, 1200)
	
	return
	
	var n = {}
	var v = Vector2i(1, 2)
	
	n[v] = 4
	
	print(n[Vector2i(1, 2)])
	
	# Stop
	
	var data = WorldData.new()
	
	_world_data = data
	
	explorer.add_ground_textures(t, 3.0)
	
	

func _input(event):
	if event is InputEventKey and event.pressed:
		_world_data.roate_clockwise()
		
		
func _notification(what):
	if what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_IN:
		print("focus in")
	elif what == MainLoop.NOTIFICATION_APPLICATION_FOCUS_OUT:
		print("focus out")
