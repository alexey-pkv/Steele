extends Control

func _input(event):
	if Input.is_action_pressed("ui_cancel"):
		get_tree().change_scene_to_file("res://Test_Scene.tscn")

func _on_play_pressed():
	get_tree().change_scene_to_file("res://Test_Scene.tscn")

func _on_options_pressed():
	get_tree().change_scene_to_file("res://Components/UI/MainMenu/Options/OptionsMenu.tscn")

func _on_quit_pressed():
	get_tree().quit()
