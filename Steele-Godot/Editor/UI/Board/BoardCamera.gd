extends Camera2D


var drag_speed 	= 50
var zoom_speed 	= 0.1
var init_zoom  	= Vector2(1, 1)
var init_offcet	= Vector2(0, 0)
var drag_start 	= Vector2()
var is_dragging = false
var min_zoom 	= Vector2(0.4, 0.4)
var max_zoom 	= Vector2(4, 4)


func mouse_events_handler(event: InputEventMouseButton):
	if event.button_index == MOUSE_BUTTON_MIDDLE:
		set_dragging(event)
	
func keyboard_events_handler(event: InputEventKey):
	if event.keycode == KEY_R:
		reset()
			
func reset():
	offset = init_offcet

func zoom_camera(zoom_factor, mouse_position):
	var viewport_size = get_viewport().size
	var previous_zoom = zoom

	zoom = clamp(zoom + zoom * zoom_factor, min_zoom, max_zoom)
#	offset += ((viewport_size * 0.5) - mouse_position) * (zoom - previous_zoom)
	
func set_dragging(event):
	if event.pressed:
		is_dragging = true
		drag_start = get_global_mouse_position()
	else:
		is_dragging = false
		
func drag_camera(event):
	print(is_dragging)
	
	if is_dragging and event is InputEventMouseMotion:
		var drag_end = get_global_mouse_position()
		var drag_vector = drag_end - drag_start
		
		offset -= drag_vector * drag_speed * get_process_delta_time()


func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_MIDDLE:
			set_dragging(event)
	
	if is_dragging:
		drag_camera(event)
