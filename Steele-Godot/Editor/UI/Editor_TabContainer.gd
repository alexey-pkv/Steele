extends TabContainer
class_name Editor_Tabs


const ATLAS_TAB_SCENE = preload("res://Editor/Tabs/AtlasViewTab.tscn")


func _add_tab(tab_scene: PackedScene, id: ResourceID) -> GenericTab:
	var tab: GenericTab = tab_scene.instantiate()
	var index = get_tab_count()
	
	add_child(tab)
	
	set_tab_title(index, id.short_name)
	current_tab = index
	
	tab.resource_id = id
	tab.load_resource()
	
	return tab


func _open_floor_atlas(data: AtlasData) -> void:
	_add_tab(ATLAS_TAB_SCENE, data.id)


func open_resource(id: ResourceID) -> void:
	var data = TemplatesRegistryNode.global().get_data(id)
	
	if data == null:
		push_error("Failed to open resource " + id.path)
		return
	
	if data.type == TemplateType.TYPE_GROUND_ATLAS:
		_open_floor_atlas(data)
	else:
		push_error("No tab for resource of type " + data.type)
	



