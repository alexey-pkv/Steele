extends Node2D
class_name TestMvoingShape


@export var velocity:		Vector2		= Vector2.ZERO
@export var allowed_area:	Rect2		= Rect2(0, 0, 100, 100)
@export var color: Color:
	get: return $ColorRect.color
	set(c): $ColorRect.color = c


func _process(delta):
	position += velocity * delta
	
	var changed = false
	
	if !allowed_area.has_point(position):
		if allowed_area.position.x > position.x:
			if velocity.x < 0: 
				velocity.x *= -1
				changed = true
		elif allowed_area.size.x + allowed_area.position.x < position.x:
			if velocity.x > 0: 
				velocity.x *= -1
				changed = true
			
		if allowed_area.position.y > position.y:
			if velocity.y < 0: 
				velocity.y *= -1
				changed = true
		elif allowed_area.size.y + allowed_area.position.y < position.y:
			if velocity.y > 0: 
				velocity.y *= -1
				changed = true
	
	if changed:
		on_velocity_changed.emit(velocity)
	
signal on_velocity_changed(v)
