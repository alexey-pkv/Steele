extends Control



func _ready():
	
	var atlas = ResourceFloorAtlas.new()
	
	atlas.texture = load("res://Resources/Editor/Steele/Floors/Cobbolt.floor.png")
	atlas.name = "Cobbolt"
	atlas.module = "Steele"
	atlas.path = "Editor/Steele/Floors"
	
	atlas.setup()
	
	atlas.get_texture(0, Direction.NORTH)
	
	print(atlas.row(1).full_path)
	print(atlas.row(1).get_direction(2).full_path)
	
	print(atlas)
	
	$Sprite2D.texture = atlas.get_texture(0, Direction.NORTH)

