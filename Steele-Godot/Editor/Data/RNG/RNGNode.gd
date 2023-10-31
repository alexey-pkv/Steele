extends Node
class_name RNGNode


var m_rng: XoroshiroRNG = XoroshiroRNG.new()


@export var seed: String = "":
	get: return seed
	set(s): 
		seed = s
		m_rng.reset_seed(s)
		reset()

@export var rnd_offset: int = 0:
	get: return rnd_offset
	set(i): 
		rnd_offset = i
		reset()


func reset() -> void:
	m_rng.reset_to_reference_i(rnd_offset)
	

func next() -> void:
	rnd_offset += 1

func prev() -> bool:
	var curr = rnd_offset
	
	if curr > 0:
		rnd_offset = curr - 1
		return true
	
	return false
	
	
func next_int() -> int:
	return m_rng.next_int()
	
func next_int_r(min: int, max: int) -> int:
	return m_rng.next_int_r(min, max)
	
func next_bool() -> int:
	return m_rng.next_bool()
	
func next_float() -> int:
	return m_rng.next_float()
	
func next_float_r(min: float, max: float) -> int:
	return m_rng.next_float_r(min, max)
	

