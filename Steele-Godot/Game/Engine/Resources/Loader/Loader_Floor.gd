class_name Loader_Floor


const FLOOR_SIZE: Vector2 = Vector2(32, 16)
const FLOOR_FILES: Array[String] = [
		".floor.png",
		".floor.jpg",
		".floor.jpeg",
		".floor.svg",
		".floor.webp"
	]


static func is_floor(path: String) -> bool:
	for o in FLOOR_FILES:
		if path.ends_with(o):
			return true
	
	return false


static func fail_on_size(img: Image) -> ResourceID:
	push_error("Floor texture must be in dimensions (" + 
		str(FLOOR_SIZE.x * 4) + "x" + str(FLOOR_SIZE.y) + "n), " + 
		"got " + str(img.get_width()) + "x" + str(img.get_height()) + "), instead" )

	return null


static func load_floor(path: String) -> ResourceID:
	var img = Image.load_from_file(path)
	
	if img == null:
		push_error("Path is not an image")
		return null;
	
	if img.get_width() != FLOOR_SIZE.x * 4:
		return fail_on_size(img)
	if img.get_height() % int(FLOOR_SIZE.y) != 0:
		return fail_on_size(img)
	
	var rows = int(img.get_height() / FLOOR_SIZE.y)
	var texture = load(path)
	var id = Resources_Common.get_resource_id(path)
	
	var atlas_data = AtlasData.create_gound_atlas(id)
	
	atlas_data.cell_size = FLOOR_SIZE
	atlas_data.rows = rows
	
	TexturesRegistryNode.g_add_ground_textures(texture, id, rows)
	TemplatesRegistryNode.g_add_atlas(atlas_data)
	
	return id

