extends TabBar


func _ready():
	self.set_current_tab(1)


func _on_tab_changed(tab):
	match tab:
		0:
			get_tree().root.content_scale_factor = 0.7
		1:
			get_tree().root.content_scale_factor = 1
		2:
			get_tree().root.content_scale_factor = 2
