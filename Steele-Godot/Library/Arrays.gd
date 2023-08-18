class_name Arrays


static func sum_f(arr: Array) -> float:
	var res: float = 0
	
	for i in arr:
		res += float(i)
	
	return res


static func sum_i(arr: Array) -> int:
	var res: int = 0
	
	for i in arr:
		res += int(i)
	
	return res
