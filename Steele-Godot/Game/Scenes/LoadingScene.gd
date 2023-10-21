@tool
extends Control


const RESOURCES = [
	"res://Resources/Editor",
	"user://Resources/Editor"
]


var _total: float = 0


@export var resources_node: GameResourcesNode: 
	get: return resources_node 
	set(node): resources_node = node

var async_state: AsyncState:
	get:
		return $AsyncNode.state


func _get_configuration_warnings():
	if resources_node == null:
		return ["A GameResourcesNode must be set. See resources_node property"]
	
	return []
	

func _load_file(count: int, file_data: RLItemData) -> void:
	$ResourceName.text = file_data.full_path
	$ProgressBar.value = float(count) / _total
	
	if resources_node != null:
		resources_node.load_file(file_data.full_path)
	
func _on_loaded(count: int) -> void:
	on_complete.emit()


func _on_counted(count: int) -> void:
	_total = float(count)
	
	RecursiveLoader.load_files(
		self.RESOURCES,
		_load_file,
		_on_loaded,
		async_state)


func begin() -> void:
	if resources_node == null:
		push_error("Missing resources node!")
	else:
		RecursiveLoader.count(
			self.RESOURCES, 
			_on_counted, 
			async_state)


signal on_complete
