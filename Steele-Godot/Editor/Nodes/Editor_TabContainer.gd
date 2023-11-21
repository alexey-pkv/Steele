extends TabContainer
class_name Editor_Tabs


const ATLAS_TAB_SCENE = preload("res://Editor/Tabs/AtlasViewTab.tscn")

const TEST_SCENE = preload("res://Editor/Tabs/PaletteTab.tscn")


func _add_tab(tab_scene: PackedScene, id: int) -> GenericTab:
	var tab: GenericTab = tab_scene.instantiate()
	var index = get_tab_count()
	var data = Resources.get_id(id)
	
	add_child(tab)
	
	set_tab_title(index, data.name)
	current_tab = index
	
	tab.resource_id = id
	tab.load_resource()
	
	return tab

func find_tab_index(id: int) -> int:
	var chilren = get_children();
	
	for i in range(len(chilren)):
		var child = chilren[i]
		
		if !(child is GenericTab):
			continue
		
		if id == child.resource_id:
			return i
	
	return -1
	
func select_tab(id: int) -> bool:
	var index = find_tab_index(id)
	
	if index == -1:
		return false
	
	current_tab = index
	
	return true


func _open_floor_atlas(data: ResourceFloorAtlas) -> void:
	if select_tab(data.id):
		return
	
	_add_tab(ATLAS_TAB_SCENE, data.id)


func open_test(id: int = SteeleID.NULL_ID) -> void:
	if id == null:
		id = 1
	
	_add_tab(TEST_SCENE, id)

func open_resource(id: int) -> void:
	var data = Resources.get_id(id)
	
	if data == null:
		push_error("Failed to open resource " + str(id))
		return
	
	if data.type == SteeleResource.TYPE_FLOOR_ATLAS:
		_open_floor_atlas(data)
	else:
		push_error("No tab for resource of type " + data.type)
	


