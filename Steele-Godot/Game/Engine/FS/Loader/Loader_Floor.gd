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


static func fail_on_size(img: Image) -> int:
	push_error("Floor texture must be in dimensions (" + 
		str(FLOOR_SIZE.x * 4) + "x" + str(FLOOR_SIZE.y) + "n), " + 
		"got " + str(img.get_width()) + "x" + str(img.get_height()) + "), instead" )

	return SteeleID.NULL


static func load_floor(path: String) -> int:
	var atlas = ResourceFloorAtlas.new()
	
	var image = Image.load_from_file(path)
	var image_texture = ImageTexture.create_from_image(image)
	
	atlas.texture = image_texture
	atlas.setup(path)
	
	return atlas.id

