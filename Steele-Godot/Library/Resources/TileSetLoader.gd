class_name TileSetLoader


const EXTENSION			= '.png'


static func __get_size(file_name: String) -> Vector2:
	var sizeString: String = ""
	var parts = file_name.split('.')
	var regex = RegEx.new()
	
	regex.compile('^[0-9]*x[0-9]*$')
	
	for part in parts:
		if regex.search(part) != null:
			sizeString = part
			break
	
	if sizeString == "":
		return Vector2(0, 0)
	
	var sizeParts = sizeString.split('x')
	
	if len(sizeParts) != 2:
		return Vector2(0, 0)
	
	var x = int(sizeParts[0])
	var y = int(sizeParts[1])
	
	if x < 0 || y < 0:
		return Vector2(0, 0)
	
	return Vector2(x, y)


static func __get_sub_texture(source: Texture2D, offset: Vector2, size: Vector2) -> Texture2D:
	var texture = AtlasTexture.new()
	
	texture.atlas = source
	texture.region = Rect2(offset, size)
	
	return texture


static func load(path: String, into: GroundTextures = null) -> GroundTextures:
	if into == null:
		into = GroundTextures.new()
	
	var name = path.get_file().split('.')[0]
	var cellSize = __get_size(path.get_file())
	var texture: Texture2D = load(path)
	var textureSize = texture.get_size()
	
	if int(textureSize.x) % int(cellSize.x) != 0 || \
			int(textureSize.y) % int(cellSize.y) != 0 || \
			textureSize.x / cellSize.x != 4: 
		
		print("incorrect tileset size for " + path)
		return into
	
	for y in range(0, textureSize.y / cellSize.y):
		var textureSet = GroundTexture.create_from_textures(
			name + "." + str(y),
			__get_sub_texture(texture, Vector2(0 * cellSize.x, y * cellSize.y), cellSize),
			__get_sub_texture(texture, Vector2(1 * cellSize.x, y * cellSize.y), cellSize),
			__get_sub_texture(texture, Vector2(2 * cellSize.x, y * cellSize.y), cellSize),
			__get_sub_texture(texture, Vector2(3 * cellSize.x, y * cellSize.y), cellSize)
		)
		
		into.add_texture(textureSet)
	
	return into
	
