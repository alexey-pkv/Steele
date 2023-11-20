extends Node2D


func copy_files(source: String, target: String) -> void:
	var dir_source: DirAccess = DirAccess.open(source)
	var dir_target: DirAccess = DirAccess.open(target)
	
	var target_files = dir_target.get_files()
	
	for local_file in dir_source.get_files():
		if local_file.ends_with(".import"):
			continue
		if target_files.has(local_file):
			continue
		
		var source_file = source + "/" + local_file
		var target_file = target + "/" + local_file
		
		print(" - Copy File: " + source_file + " -> " + target_file)
		
		dir_target.copy(source_file, target + "/" + local_file)
	

func copy(source: String, target: String) -> void:
	var dir_source: DirAccess = DirAccess.open(source)
	var dir_target: DirAccess = DirAccess.open(target)
	
	var target_dirs = dir_target.get_directories()
	
	for local_dir in dir_source.get_directories():
		if !target_dirs.has(local_dir):
			var source_dir = source + "/" + local_dir
			var target_dir = target + "/" + local_dir
			
			print("Copy Dir: " + source_dir + " -> " + target_dir)
			
			dir_target.make_dir(local_dir)
		
		copy(
			source + "/" + local_dir,
			target + "/" + local_dir
		)
	
	copy_files(source, target)


func _ready():
	var target: String = OS.get_user_data_dir()
	var source: String = "res://Resources/Game"
	
	copy(source, target)
