extends TabContainer
class_name Editor_Tabs


const ATLAS_TAB_SCENE = preload("res://Editor/Tabs/AtlasViewTab.tscn")

const TEST_SCENE = preload("res://Editor/Tabs/AreaEditorTab.tscn")


func _add_tab(tab_scene: PackedScene, id: ResourceID) -> GenericTab:
	var tab: GenericTab = tab_scene.instantiate()
	var index = get_tab_count()
	
	add_child(tab)
	
	set_tab_title(index, id.short_name)
	current_tab = index
	
	tab.resource_id = id
	tab.load_resource()
	
	return tab

func find_tab_index(id: ResourceID) -> int:
	var chilren = get_children();
	
	for i in range(len(chilren)):
		var child = chilren[i]
		
		if !(child is GenericTab):
			continue
		
		if id.equals(child.resource_id):
			return i
	
	return -1
	
func select_tab(id: ResourceID) -> bool:
	var index = find_tab_index(id)
	
	if index == -1:
		return false
	
	current_tab = index
	
	return true


func _open_floor_atlas(data: AtlasData) -> void:
	if select_tab(data.id):
		return
	
	_add_tab(ATLAS_TAB_SCENE, data.id)


func open_test() -> void:
	var id = ResourceID.new()
	id.short_name = "test"
	
	_add_tab(TEST_SCENE, id)

func open_resource(id: ResourceID) -> void:
	var data = TemplatesRegistryNode.global().get_data(id)
	
	if data == null:
		push_error("Failed to open resource " + id.path)
		return
	
	if data.type == TemplateType.TYPE_GROUND_ATLAS:
		_open_floor_atlas(data)
	else:
		push_error("No tab for resource of type " + data.type)
	


