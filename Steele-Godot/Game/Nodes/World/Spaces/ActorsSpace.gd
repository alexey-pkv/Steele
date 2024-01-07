extends ObjectSpace
class_name ActorsSpace


var SCENE_Actor = preload("res://Game/Nodes/World/Actor.tscn")


var actors_by_id:		Dictionary = {}
var moving_actors:		Dictionary = {}


var actors_count: int:
	get: return len(actors_by_id)

var moving_actors_count: int:
	get: return len(moving_actors)


func handle_actor_arrived_at_cell(id: int, from: Vector3i, to: Vector3i) -> void:
	if !(id in actors_by_id):
		return
	
	move_object_cells(actors_by_id[id], from, to)


func create_actor(at: Vector3i) -> Actor:
	var actor: Actor = SCENE_Actor.instantiate()
	
	
	add_object_cell(actor, at)
	
	return actor

func get_actor_id(id: int) -> Actor:
	return null

func remove_actor(id: int) -> void:
	pass

func has_actor(id: int) -> bool:
	return false
