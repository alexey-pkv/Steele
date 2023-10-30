@tool
extends AbstractResourceExplorerItem
class_name FloorItem



var c_floor: GroundSprite2D:
	get:
		return $GroundSprite2D if is_inside_tree() else null


func _update() -> void:
	var f = c_floor
	
	if f == null:
		return
	
	f.ground_id = resource_id


func _ready():
	if is_inside_tree():
		_update()

func _enter_tree():
	_update()


func _on_gui_input(event):
	if event is InputEventMouseButton:
		if event.is_pressed() && event.button_index == 1:
			on_pressed.emit(resource_id)


func select() -> void:
	$ColorRect.visible = true

func deselect() -> void:
	$ColorRect.visible = false


signal on_pressed(id: ResourceID)
