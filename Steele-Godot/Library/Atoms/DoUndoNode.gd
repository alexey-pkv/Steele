extends Node
class_name DoUndoNode


var MAX_SIZE:	int		= 1000

var m_stack:	Array	= []
var m_index:	int		= -1


func all() -> Array:
	return m_stack

func head() -> IDoable:
	if is_empty():
		return null
	
	return m_stack[m_index]

func count() -> int:
	return len(m_stack)

func is_empty() -> bool:
	return len(m_stack) == 0

func is_at_capacity() -> bool:
	return count() >= MAX_SIZE

func index() -> int:
	return m_index

func last_index() -> int:
	return len(m_stack) - 1

func can_undo() -> bool:
	return m_index >= 0

func can_redo() -> bool:
	return m_index < last_index()


func push(d: IDoable) -> void:
	if can_redo():
		m_stack = m_stack.slice(0, m_index)
	
	m_stack.push_back(d)
	m_index += 1
	
	while (is_at_capacity()):
		m_stack.remove_at(0)
		m_index -= 1
	
	on_modified.emit()

func clear() -> void:
	if len(m_stack) == 0:
		return
	
	m_index = -1
	m_stack.clear()
	
	on_modified.emit()

func do(d: IDoable) -> void:
	push(d)
	d.do()

func undo() -> bool:
	if !can_undo():
		return false
	
	head().undo()
	m_index -= 1
	
	on_modified.emit()
	
	return true

func redo() -> bool:
	if !can_redo():
		return false
	
	m_index += 1
	head().do()
	
	on_modified.emit()
	
	return true


signal on_modified()
