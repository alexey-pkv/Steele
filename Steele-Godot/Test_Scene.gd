extends Control


var db: ResourcesDBNode:
	get: return $ResourcesDBNode

var n: AreaSelect:
	get: return $AreaSelect

var b = FillBrush.new()

func _ready():
	db.add_fill_brush(12, b)
	print(db.has(12))
	




func _on_timer_timeout():
	print("Timer")
	print(db.has(12))
	print(db.count())
	
	b = null
