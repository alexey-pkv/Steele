class_name Palette


var _selfPalette:		Palette			= null
var _basePalettes:	Array[Palette]	= []


var name:			String
var ground_palette:	GroundPalette


func _handle_component_modified() -> void:
	if len(_basePalettes) != 0:
		_combine()
	
	DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN
	on_modified.emit()

func _combine() -> void:
	return


func _init(name: String):
	name = name
	
	ground_palette = GroundPalette.new()
	
	ground_palette.on_modified.connect(_handle_component_modified)





signal on_modified()
