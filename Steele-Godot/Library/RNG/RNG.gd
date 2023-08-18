extends IAlgo
class_name RNG


var _algo:			IAlgo
var _seed:			Array[int]
var _seed_string:	String
var _offset:		int


const INT64_MAX = 9223372036854775807


static func get_int64_array(seed: String) -> PackedInt64Array:
	var buffer = seed.to_ascii_buffer()
	var offset = 0
	
	while len(buffer) % 8 != 0:
		buffer.push_back(buffer[offset])
		offset = offset + 1
	
	return buffer.to_int64_array()

static func extend_int64_array(buffer: PackedInt64Array, min_size: int) -> PackedInt64Array:
	var offset = 0
	
	while len(buffer) < min_size:
		buffer.push_back(buffer[offset])
		offset = offset + 1
	
	return buffer


static func _get_int_seed(seed: String) -> Array[int]:
	if len(seed) == 0: seed = " "
	
	var packed		:= get_int64_array(seed)
	var sha256		:= seed.sha256_buffer().to_int64_array()
	var sha_offset	:= 0
	
	var result: Array[int]	= []
	
	packed = extend_int64_array(packed, len(sha256))
	
	for val in packed:
		result.push_back(val ^ (sha256[sha_offset]))
		sha_offset = (sha_offset + 1) % len(sha256)
	
	return result


func _neex_seed_int() -> int:
	var i = _seed[_offset]
	
	_offset = _offset + 1
	
	if _offset == len(_seed):
		_offset = 0
	
	return i


func _init(algo: IAlgo, seed: String):
	_algo = algo
	_seed_string = seed
	_seed = _get_int_seed(seed)
	_offset = 0


func next_int() -> int: 
	return _algo.next_int() ^ _neex_seed_int()

func next_int_range(from: int, to: int) -> int: 
	if from == to:
		return from
	elif from > to:
		var a = to
		to = from
		from = a
	
	return _algo.next_int_range(from, to);

func next_float() -> float: 
	return _algo.next_float()

func next_float_range(from: float, to: float) -> float: 
	if from == to:
		return from
	elif from > to:
		var a = to
		to = from
		from = a
	
	return _algo.next_float_range(from, to);
	
func next_weighted_dictionary(dict: Dictionary, total: float = -1) -> String:
	if total == -1:
		total = Arrays.sum_f(dict.values())
	
	if total == 0:
		return ""
	
	var rnd:	float	= next_float_range(0, total);
	var result:	String	= ""
	
	for key in dict:
		rnd -= dict[key]
		result = key
		
		if rnd <= 0:
			break;
	
	return result
	

func next_weighted_index(weights: Array) -> int:
	var rnd:	float	= next_float_range(0, Arrays.sum_f(weights));
	
	for i in len(weights):
		rnd -= weights[i]
		
		if rnd <= 0:
			return i
	
	return len(weights) - 1


func randomize() -> void:
	_algo.randomize()
	_seed = [_algo.next_int()]
	_algo.randomize()


func load(data: Dictionary) -> void:
	_seed_string	= data['seed']
	_seed			= _get_int_seed(_seed_string)
	_offset			= data['offset']
	
	_algo.load(data['algo'])

func save() -> Dictionary:
	return {
		'seed':		_seed_string, 
		'offset':	_offset,
		'algo':		_algo.save()
	}


static func create_godot_algo(seed: String) -> RNG:
	return RNG.new(GodotAlgo.new(), seed)
