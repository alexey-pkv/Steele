@tool
class_name Game


const TIME_FLOW_REAL_TIME	= 0
const TIME_FLOW_PAUSED		= 1
const TIME_FLOW_TURN_BASED	= 2


static var time_flow:	int		= TIME_FLOW_REAL_TIME

static var cell_size:	Vector3	= Vector3(32, 16, 32)
static var cell_offset:	Vector2	= Vector2.ZERO

static var chunk_size:		Vector3i		= Vector3i(16, 16, 16)
static var chunk_offset:	Vector3i		= Vector3i.ZERO


static func get_chunk_index(at_cell: Vector3i) -> Vector3i:
	return Vector3i(
		at_cell.x / chunk_size.x,
		at_cell.y / chunk_size.y,
		at_cell.z / chunk_size.z
	)
	
static func get_chunk_offset(at_chunk: Vector3i) -> Vector3i:
	return Vector3i(
		at_chunk.x * chunk_size.x,
		at_chunk.y * chunk_size.y,
		at_chunk.z * chunk_size.z
	)

static func world_position_to_real_position(at: Vector3) -> Vector2:
	return Isometric.grid_to_local_v3(at, cell_size)

static func is_real_time() -> bool:
	return time_flow == TIME_FLOW_TURN_BASED
	
static func is_paused() -> bool:
	return time_flow == TIME_FLOW_PAUSED
	
static func is_turn_based() -> bool:
	return time_flow == TIME_FLOW_TURN_BASED

