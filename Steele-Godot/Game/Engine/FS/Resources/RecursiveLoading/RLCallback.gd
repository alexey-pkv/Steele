extends RefCounted
class_name RLCallback


func handle_file(_data: RLItemData) -> void:
	pass

func handle_dir(_data: RLItemData) -> bool:
	return true

func handle(_data: RLItemData) -> void:
	pass


func invoke(path: String) -> bool:
	var is_file = FileAccess.file_exists(path)
	
	if !is_file && !DirAccess.dir_exists_absolute(path):
		return false;
	
	var result: bool = true
	var data: RLItemData = RLItemData.new(is_file, path)
	
	handle(data)
	
	if data.is_file:
		handle_file(data)
	else:
		result = handle_dir(data)
	
	data.free()
	
	return result

class RLFuncCallback:
	extends RLCallback
	
	
	var m_file_callback: Callable
	var m_dir_callback: Callable
	var m_def_callback: Callable
	
	
	func handle_file(data: RLItemData) -> void:
		if !m_file_callback.is_null():
			m_file_callback.call(data)

	func handle_dir(data: RLItemData) -> bool:
		if !m_dir_callback.is_null():
			return m_dir_callback.call(data)
		
		return true

	func handle(data: RLItemData) -> void:
		if !m_def_callback.is_null():
			m_def_callback.call(data)


static func create_callback_by_type(file_callback: Callable, dir_callback: Callable, def_callback: Callable) -> RLCallback:
	var c: RLFuncCallback = RLFuncCallback.new()
	
	c.m_file_callback = file_callback
	c.m_dir_callback = dir_callback
	c.m_def_callback = def_callback
	
	return c

static func create_callback(callback: Callable) -> RLCallback:
	var c: RLFuncCallback = RLFuncCallback.new()
	
	c.m_def_callback = callback
	
	return c
	
	
















