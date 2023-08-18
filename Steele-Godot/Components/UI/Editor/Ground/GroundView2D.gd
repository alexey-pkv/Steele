extends Node2D
class_name GroundView2D


@onready var north_ground:	GroundSprite2D	= $North
@onready var east_ground:	GroundSprite2D	= $East
@onready var south_ground:	GroundSprite2D	= $South
@onready var west_ground:	GroundSprite2D	= $West


var world_data: WorldData = null: 
	set(value):
		if world_data != null:
			world_data.on_direction_changed.disconnect(_handle_direction_changed)
		
		world_data = value
		
		north_ground.world_data = value
		east_ground.world_data = value
		south_ground.world_data = value
		west_ground.world_data = value
		
		if world_data != null:
			world_data.on_direction_changed.connect(_handle_direction_changed)
	get: 
		return world_data


@export var ground_texture: GroundTexture:
	set(value):
		ground_texture = value
		
		if north_ground == null:
			return
		
		north_ground.ground_texture = value
		east_ground.ground_texture = value
		south_ground.ground_texture = value
		west_ground.ground_texture = value
	get:
		return ground_texture

@export var cell_spacing: int = 32:
	set(value):
		cell_spacing = value
		_update_positions()
	get:
		return cell_spacing

@export var cell_width: int = 32:
	set (value):
		cell_width = value
		_update_positions()
	get:
		return cell_width


func _handle_direction_changed(direction: int, original: int) -> void:
	north_ground.update_sprite()
	east_ground.update_sprite()
	south_ground.update_sprite()
	west_ground.update_sprite()
	
func _update_positions() -> void:
	if north_ground == null:
		return
	
	var single_offset = cell_width + cell_spacing
	
	north_ground.position.x	= 0
	east_ground.position.x	= single_offset
	south_ground.position.x	= single_offset * 2
	west_ground.position.x	= single_offset * 3


func _ready():
	_update_positions()
	
	north_ground.direction	= Direction.NORTH
	east_ground.direction	= Direction.EAST
	south_ground.direction	= Direction.SOUTH
	west_ground.direction	= Direction.WEST
	
	north_ground.ground_texture = ground_texture
	east_ground.ground_texture = ground_texture
	south_ground.ground_texture = ground_texture
	west_ground.ground_texture = ground_texture

