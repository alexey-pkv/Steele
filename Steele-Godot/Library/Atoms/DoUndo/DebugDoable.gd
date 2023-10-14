extends IDoable
class_name DebugDoable


var m_name: String


func _init(name: String):
	m_name = name


func name() -> String:
	return m_name

func do() -> void:
	print("Do " + m_name)

func undo() -> void:
	print("Undo " + m_name)

