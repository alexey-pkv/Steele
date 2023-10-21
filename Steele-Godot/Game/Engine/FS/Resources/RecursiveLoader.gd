class_name RecursiveLoader


const COUNT_STYLE_FILES_ONLY		= 0
const COUNT_STYLE_FILES_AND_DIRS	= 1


class _counter_class_:
	extends Object
	
	var count: int = 0:
		get: return count
	
	func add() -> void:
		count += 1


static func count(path, callback: Callable, state: AsyncState = null, count_style: int = COUNT_STYLE_FILES_ONLY) -> AsyncState: 
	if state == null:		state = AsyncState.new()
	if !(path is Array):	path = [path]
	
	var counter = _counter_class_.new()
	
	var counter_callback = RLCallback.create_callback(
		func(data: RLItemData): 
			if data.is_dir:
				if count_style == COUNT_STYLE_FILES_AND_DIRS:
					counter.add()
			else:
				counter.add()
	)
	
	if !(path is Array):
		path = [path]
	
	for p in path:
		RecursiveIterator.iterate(state, counter_callback, p)
	
	state.on_complete(func():
		callback.call(counter.count)
		counter.free())
	
	return state
	
static func load_files(path, callback: Callable, on_complete: Callable, state: AsyncState = null, count_style: int = COUNT_STYLE_FILES_ONLY) -> AsyncState: 
	if state == null:	state = AsyncState.new()
	if !(path is Array): path = [path]
	
	var counter = _counter_class_.new()
	
	var file_callback = func(data: RLItemData):
		callback.call(counter.count, data)
	
	var counter_callback = func(data: RLItemData):
		if data.is_dir:
			if count_style == COUNT_STYLE_FILES_AND_DIRS:
				counter.add()
		else:
			counter.add()
	
	var counter_object = RLCallback.create_callback_by_type(
		file_callback,
		Callable(),
		counter_callback
	)
	
	for p in path:
		RecursiveIterator.iterate(state, counter_object, p)
	
	state.on_complete(
		func():
			on_complete.call(counter.count)
			counter.free()
	)
	
	return state
