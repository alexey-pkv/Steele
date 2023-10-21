extends RefCounted
class_name RecursiveIterator


static var __debug__: bool = false


static func iterate(async: AsyncState, callback: RLCallback, path: String) -> void:
	var dir: DirAccess = DirAccess.open(path)
	
	
	var file_callback = func(p_path): 
		if RecursiveIterator.__debug__:
			print("Loading file " + p_path)
			
		callback.invoke(p_path)
		
	
	if RecursiveIterator.__debug__:
		print("Loading " + path)
	
	if !dir:
		if RecursiveIterator.__debug__:
			print(path + " is not a directory!")
		
		return
	
	if callback.invoke(path):
		for child_dir in dir.get_directories():
			child_dir = path + "/" + child_dir
			async.defer_callback(func(): RecursiveIterator.iterate(async, callback, child_dir))
	
	for child_file in dir.get_files():
		if child_file.ends_with(".import"):
			continue
		
		child_file = path + "/" + child_file
		async.defer_callback(func(): file_callback.call(child_file))
	
