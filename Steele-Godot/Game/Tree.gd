extends Tree


func dir_contents(path):
	var files = []
	var dir = DirAccess.open(path)
	
	if dir:
		dir.list_dir_begin()
		var file_name = dir.get_next()
		
		while file_name != "":
			files.append(file_name)
			
			if dir.current_is_dir():
				print("Found directory: " + file_name)
			else:
				print("Found file: " + file_name)
				
			file_name = dir.get_next()
			
		return files
	else:
		print("An error occurred when trying to access the path.")
		
# Called when the node enters the scene tree for the first time.
func _ready():
	var files_list = dir_contents('res://Resources/TestResources/Ground/')
	var root = self.create_item()
	self.hide_root = true

	for file_name in files_list:
		var child = self.create_item(root)
		child.set_text(0, file_name)
		
		var cc = child.create_child()
		cc.set_text(0, "hello")
		cc.set_text(1, "world")

		
#	var root = self.create_item()
#	self.hide_root = true
#	var child1 = self.create_item(root)
#	var child2 = self.create_item(root)
#	var subchild1 = self.create_item(child1)
#	root.set_text(0, 'Test text')
#	child1.set_text(0, '1212')
#	subchild1.set_text(0, "Subchild1")
	print(files_list)
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass


