class_name Direction


const NORTH:	int		= 0
const EAST:		int		= 2
const SOUTH:	int		= 4
const WEST:		int		= 6

const NORTH_EAST: int	= 1
const SOUTH_EAST: int	= 3
const SOUTH_WEST: int	= 5
const NORTH_WEST: int	= 7


const NAMES		= [
	"North",
	"North East",
	"East",
	"South East",
	"South",
	"South West",
	"West",
	"North West",
]


static func get_direction_name(dir: int) -> String:
	if dir < 0 || dir > 7:
		return "Invalid Direction"
	
	return NAMES[dir]


static func rotate_clockwise(dir: int) -> int:
	return (dir + 2) % 8

static func rotate_clockwise_h(dir: int) -> int:
	return (dir + 1) % 8

static func rotate_counter_clockwise(dir: int) -> int:
	if dir <= NORTH_EAST:
		dir = dir + 8
	
	return dir - 2
	
static func rotate_counter_clockwise_h(dir: int) -> int:
	if dir <= NORTH:
		return NORTH_WEST
	
	return dir - 1

static func add(a: int, b: int) -> int:
	return (a + b) % 8

static func sub(a: int, b: int) -> int:
	a = a - b
	
	if a < NORTH:
		a = a + 8
		
	return a

static func mult(a: int, by: int) -> int:
	return (a * by) % 8

static func dir_ceil(dir: int) -> int:
	if dir == NORTH_WEST:
		return NORTH
		
	if dir % 2 == 1:
		return dir + 1
	
	return dir

static func dir_floor(dir: int) -> int:
	if dir % 2 == 1:
		return dir - 1
	
	return dir

static func random(rnd: RandomNumberGenerator) -> int:
	return rnd.randi_range(0, 3) * 2

static func rotate_v2(v: Vector2, by: int) -> Vector2:
	if by == NORTH:
		return v
	elif by == SOUTH:
		return Vector2(-v.x, -v.y)
	elif by == EAST:
		return Vector2(v.y, -v.x)
	elif by == WEST:
		return Vector2(-v.y, v.x)
	else:
		push_error("Unexpected direction: " + str(by))
		return Vector2.ZERO

static func rotate_v2i(v: Vector2i, by: int) -> Vector2i:
	if by == NORTH:
		return v
	elif by == SOUTH:
		return Vector2i(-v.x, -v.y)
	elif by == EAST:
		return Vector2i(v.y, -v.x)
	elif by == WEST:
		return Vector2i(-v.y, v.x)
	else:
		push_error("Unexpected direction: " + str(by))
		return Vector2i.ZERO
