@tool
extends ResourceTexture
class_name ResourceFloorAtlas


var m_rows: Array[int] = []


var rows: int:
	get: return len(m_rows)

var children: Array[int]:
	get: return m_rows

var cell_size: Vector2: 
	get: return cell_size


func _init(_texture: Texture2D = null):
	super(TYPE_FLOOR_ATLAS, _texture)
	is_valid = false


func row_id(index: int) -> int:
	if index < 0 || index >= len(m_rows):
		return SteeleID.NULL_ID
	
	return m_rows[index]

func row(index: int) -> ResourceFloor:
	if index < 0 || index >= len(m_rows):
		return null
	
	var res = Resources.get_id(m_rows[index])
	
	return res if res is ResourceFloor else null

func get_texture(index: int, dir: int) -> Texture2D:
	var _floor = row(index)
	
	return _floor.get_direction_texture(dir) if _floor != null else null

func _setup_floor(_row: int) -> ResourceFloor:
	var _floor = ResourceFloor.new()
	
	if !_floor.register():
		return null
	
	setup_child(_floor, str(_row))
	_floor.create_directions()
	
	var at = Vector2(0, _row * cell_size.y)
	
	for res in _floor.get_directions():
		var _texture = AtlasTexture.new()
		
		_texture.atlas = texture
		_texture.region = Rect2(at, cell_size)
		
		res.texture = _texture
		at.x += cell_size.x
	
	return _floor

func setup(from_path: String = "") -> bool:
	if !register(from_path):
		return false
	
	var width = floor(texture.get_width())
	var height = floor(texture.get_height())
	
	if width % 8 != 0:
		return false
	
	var x = width / 4
	var y = x / 2
	
	if height % y != 0:
		return false
	
	cell_size = Vector2(x, y)
	
	for i in (height / y):
		var _floor = _setup_floor(i)
		
		if _floor == null:
			return false
		
		m_rows.push_back(_floor.id)
	
	is_valid = true
	
	return true
