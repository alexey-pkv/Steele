@tool
extends Node2D
class_name ZoomFactor


const SCALE_STYLE_LINEAR	= 0
const SCALE_STYLE_RELATIVE	= 0


var m_factor_index: int = 0
var m_factor: float = 1.0


var factors_count: int:
	get: return len(factors)

var factors: Array[float] = [m_factor]:
	get: return factors

var defaultm_factor_index: int:
	get: return 0


var factor_index: int = 0:
	get:	return m_factor_index
	set(v):	zoom_to_index(v)

@export var zoom_reference: Node2D: 
	get: return zoom_reference
	set(n): 
		zoom_reference = n
		
		if n != null:
			n.scale = Vector2(m_factor, m_factor)

@export var default_factor: float = 1.0:
	get: return default_factor
	set(v): 
		default_factor = v
		_update_scale()

@export var min_factor: float = 1.0:
	get: return min_factor
	set(v): 
		if v <= 0:
			v = 1.0
		
		min_factor = v
		_update_scale()

@export var max_factor: float = 1.0:
	get: return max_factor
	set(v): 
		if v <= 0:
			v = 1.0
			
		max_factor = v
		_update_scale()

@export var factor_scale: float = 1.0:
	get: return factor_scale
	set(v): 
		factor_scale = v
		_update_scale()

@export var scale_style: int = SCALE_STYLE_LINEAR:
	get: return scale_style
	set(v): 
		scale_style = v
		_update_scale()

@export var factor: float = 1.0:
	get:	return m_factor
	set(v):	zoom_to_nearest(v)


func zoom_to_nearest(to: float) -> void:
	var _factors = factors
	var _last: float
	
	for i in range(factors_count):
		var _curr = _factors[i]
		
		if _curr < to:
			_last = _curr
			continue
		
		if i == 0:
			min_zoom()
			return
		
		if to - _last <= _curr - to:
			zoom_to_index(i - 1)
		else:
			zoom_to_index(i)
		
		return
	
	max_zoom()

func _modify_factor_to(to: float) -> void:
	if m_factor == to:
		return
	
	var _prev = m_factor;
	m_factor = to
	
	factor_changed.emit(m_factor, _prev)
	scale = Vector2(m_factor, m_factor)
	
	if zoom_reference != null:
		zoom_reference.scale = Vector2(m_factor, m_factor)

func zoom_to_index(index: int) -> void:
	if index < 0:
		min_zoom()
		return
	elif index >= factors_count:
		max_zoom()
		return
	
	var _prev = m_factor
	
	m_factor_index = index
	_modify_factor_to(factors[index])

func applay_default_zoom() -> void:
	zoom_to_nearest(default_factor)

func zoom_in() -> void:
	zoom_to_index(factor_index + 1)

func zoom_out() -> void:
	zoom_to_index(factor_index - 1)

func min_zoom() -> void:
	zoom_to_index(0)
	
func max_zoom() -> void:
	zoom_to_index(factors_count - 1)


func _update_scale() -> void:
	var _min: float 			= min_factor
	var _max: float 			= max_factor
	var _def: float				= default_factor
	var _factors: Array[float]	= []
	var _curr: float
	
	_curr = _def
	
	while (_curr >= _min):
		if _curr != _def:
			_factors.push_front(_curr)
		
		if scale_style == SCALE_STYLE_LINEAR:
			_curr -= factor_scale
		else:
			_curr = _curr * (1 - factor_scale)
	
	defaultm_factor_index = len(_factors)
	
	_factors.push_back(_def)
	_curr = _def
	
	while (_curr <= _max):
		if _curr != _def:
			_factors.push_back(_curr)
		
		if scale_style == SCALE_STYLE_LINEAR:
			_curr += factor_scale
		else:
			_curr = _curr * (1 + factor_scale)
	
	factors = _factors
	zoom_to_nearest(factor)
	
	factor_range_changed.emit()


signal factor_changed(to: float, from: float)
signal factor_range_changed()

