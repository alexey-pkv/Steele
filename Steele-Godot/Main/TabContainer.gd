extends TabContainer


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_tree_button_clicked(item, column, id, mouse_button_index):
	print(item, column, id, mouse_button_index)
	pass # Replace with function body.


func _on_tree_child_entered_tree(node):
	print('node', node)
	pass # Replace with function body.


func _on_tree_item_selected():
	var img = TextureRect.new()
	img.name = '123'
	img.texture = load('res://Resources/TestResources/Ground/arrow.s.png')
	add_child(img)
	pass # Replace with function body.
