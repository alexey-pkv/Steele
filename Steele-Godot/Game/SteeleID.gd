@tool
class_name SteeleID


const NULL		= 0
const MIN_ID	= 1
const MAX_ID	= 2147483647


static var m_last_id	= MIN_ID - 1


static func next_id() -> int:
	if m_last_id == MAX_ID:
		m_last_id = MIN_ID
	else:
		m_last_id = m_last_id + 1
	
	return m_last_id
