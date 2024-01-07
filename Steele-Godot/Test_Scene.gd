extends Control


var SHAPE_SCENE = preload("res://TestScene/MovingShape.tscn")
var SCENE_Actor = preload("res://Game/Nodes/World/Actor.tscn")
var curr_target = 0
var shapes = 0

var m_rng: XoroshiroRNG = XoroshiroRNG.new()
var t: Thread = Thread.new()

var a

func init_actor() -> Actor:
	return SCENE_Actor.instantiate()


func actually_add_shape() -> void:
	print("adding...")
	curr_target = curr_target - 1
	
	var act: Actor = init_actor()
	var inst: TestMvoingShape = SHAPE_SCENE.instantiate()
	
	a = act
	act.set_speed(2)
	act.add_child(inst)
	
	var angle = m_rng.next_float() * PI * 2
	
	inst.color = Color(m_rng.next_float(), m_rng.next_float(), m_rng.next_float())
	
	# inst.on_velocity_changed.connect(on_changed)
	# inst.velocity = Vector2(100, 100).rotated(angle)
	# inst.allowed_area = Rect2(Vector2(100, 50), Vector2(100, 50))
	# inst.position = Vector2(m_rng.next_float_r(0, size.x), m_rng.next_float_r(0, size.y))
	
	shapes = shapes + 1
	
	act.on_arrived_at_cell.connect(_on_arrived_at)
	act.on_move_update.connect(_on_move_changed)
	act.on_move_begin.connect(_on_move_start)
	act.on_move_end.connect(_on_move_end)
	
	act.init_position_xyz(m_rng.next_int_r(2, 20), 0, 0)
	act.move_to_xyz(m_rng.next_int_r(2, 20), 0, 0)
	
	$Scene.call_deferred("add_child", act)

func do_add_shape() -> void:
	if curr_target == 0:
		OS.delay_msec(100)
	elif curr_target > 0:
		actually_add_shape()
	else:
		print("removing...")
		
		shapes = shapes - 1
		
		curr_target = curr_target + 1
	
	
	if curr_target != 0:
		# do_add_shape.call_deferred()
		pass


func _ready():
	m_rng.reset_seed("OH YEAH!")
	
func _enter_tree():
	t.start(do_add_shape, Thread.PRIORITY_HIGH)

func _process(delta):
	const ROUND_TO = 100
	
	var fps = 1 / delta
	
	var d = roundf(delta * ROUND_TO) / ROUND_TO
	var f = round(fps * ROUND_TO) / ROUND_TO
	
	$FPS.text = str(f) + " fps"
	$Delta.text = str(d) + " sec"
	$Shapes.text = str(shapes) + " shapes"
	
	var i = 0
	
	while curr_target != 0 and i < 10:
		do_add_shape()
		i = i + 1




func _add_shapes(count: int) -> void:
	print("Add " + str(count))
	
	curr_target += count
	# do_add_shape.call_deferred()


func _on_button_100_pressed():
	_add_shapes(100)

func _on_button_10_pressed():
	_add_shapes(10)

func _on_button_1_pressed():
	_add_shapes(1)

func _on_move_changed(id):
	print("Move Changed " + str(a.direction))

func _on_move_start(id):
	print("Move Start")

func _on_move_end(id):
	print("Move End")

func _on_arrived_at(id, a, b):
	print("Arrived: " + str(a) + " -> " + str(b))
