extends TileMap


class_name LocalMap



var with: int = 32
var heigt: int = 16


# Called when the node enters the scene tree for the first time.
func _ready():
	for i in range(0, with):
		var s = Sprite2D.new();
		


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
