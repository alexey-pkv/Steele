@tool
extends GridCellButtonArgs
class_name GridCellReleasedArgs


@export var released_mask: MouseButtonMask:
	get: return released_mask
	set(m): released_mask = m
