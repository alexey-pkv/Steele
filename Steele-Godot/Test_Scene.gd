extends Control


var n: AreaSelect:
	get: return $AreaSelect


func _ready():
	var i = TreeItemMetadata.new()
	
	i.item_name = "Floorz"
	i.item_path = "Steele/"
	
	print(i.rename("Floors"))

