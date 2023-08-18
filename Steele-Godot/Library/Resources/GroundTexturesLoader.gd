class_name GroundTexturesLoader


const NORTH_SUFFIX		= '_n'
const SOUTH_SUFFIX		= '_s'
const WEST_SUFFIX		= '_w'
const EAST_SUFFIX		= '_e'

const EXTENSION			= '.png'


static func load_single_resource(dir: String, name: String, suffix: String) -> Texture2D:
	var path = dir + "/" + name + suffix + EXTENSION
	
	if !FileAccess.file_exists(path):
		return null
	
	return load(path)


static func load(dir: String, name: String) -> GroundTexture:
	var northTexture = load_single_resource(dir, name, NORTH_SUFFIX)
	
	
	
	return null
