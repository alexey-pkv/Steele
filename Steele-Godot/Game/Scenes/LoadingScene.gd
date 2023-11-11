@tool
extends Control
class_name LoadingScene


var _total: float = 0


@export var with_delay: bool = false:
	get: return with_delay
	set(b): with_delay = b

@export var resources_node: GameResourcesScene: 
	get: return resources_node 
	set(node): resources_node = node


var async_state: AsyncState:
	get:
		return $AsyncNode.state


func _get_configuration_warnings():
	if !is_inside_tree():
		return []
	
	if resources_node == null:
		return ["A GameResourcesScene must be set. See resources_node property"]
	
	return []
	

func _load_file(count: int, file_data: RLItemData) -> void:
	$ResourceName.text = file_data.full_path
	$ProgressBar.value = float(count) / _total
	
	if resources_node != null:
		resources_node.load_file(file_data.full_path)
	
func _on_loaded(_count: int) -> void:
	if with_delay:
		$TimerComplete.start()
	else:
		on_complete.emit()

func exec_begin() -> void:
	if resources_node == null:
		push_error("Missing resources node!")
	else:
		RecursiveLoader.count(
			Resources_Common.RESOURCES_PATH, 
			_on_counted, 
			async_state)

func begin() -> void:
	if with_delay:
		$TimerBegin.start()
	else:
		exec_begin()


func _on_counted(count: int) -> void:
	_total = float(count)
	
	RecursiveLoader.load_files(
		Resources_Common.RESOURCES_PATH,
		_load_file,
		_on_loaded,
		async_state)

func _on_timer_timeout():
	exec_begin()

func _on_timer_complete_timeout():
	on_complete.emit()


signal on_complete
