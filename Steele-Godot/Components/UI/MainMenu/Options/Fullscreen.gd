extends Button


func _on_pressed():
	var is_fullscreen = DisplayServer.window_get_mode()

	if is_fullscreen:
		self.text = 'Turn on fullscreen'
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)
	else:
		self.text = 'Turn off fullscreen'
		DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
