#ifndef STEELE_UTILS_H
#define STEELE_UTILS_H


#include <map>
#include <memory>
#include <vector>
#include <algorithm>


template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using uptr = std::unique_ptr<T>;


template <typename T>
inline bool contains(const std::vector<T>& v, const T& t)
{
	return std::find(v.begin(), v.end(), t) != v.end();
}

template <typename K, typename V>
inline bool contains(const std::map<K, V>& map, const K& k)
{
	return map.find(k) != map.end();
}

template <typename K, typename V>
inline V* get_value_ptr(std::map<K, V>& map, const K& k)
{
	auto kvp = map.find(k);
	return kvp != map.end() ? &(kvp->second) : nullptr;
}

template <typename K, typename V>
inline const V* get_value_ptr(const std::map<K, V>& map, const K& k)
{
	auto kvp = map.find(k);
	return kvp != map.end() ? &(kvp->second) : nullptr;
}

template <typename T>
inline bool remove_first_value(std::vector<T>& v, T& t)
{
	auto at = std::find(v.begin(), v.end(), t);
	
	if (at == v.end())
		return false;
	
	v.erase(at);
	
	return true;
}

template <typename K, typename V>
inline bool remove(std::map<K, V>& map, const K& k)
{
	return map.erase(k) > 0;
}

template <typename T>
int remove_until(std::vector<T>& v, typename std::vector<T>::iterator until)
{
	int count;
	
	if (until == v.begin())
	{
		count = 0;
	}
	else if (until == v.end())
	{
		count = v.size();
		v.clear();
	}
	else
	{
		count = until - v.begin();
		v.erase(v.begin(), until);
	}
	
	return count;
}

template <typename T>
inline int remove_until_index(std::vector<T>& v, int index)
{
	return remove_until(v, v.begin() + index);
}

template <typename T>
inline int remove_until_index(std::vector<T>& v, size_t index)
{
	return remove_until(v, v.begin() + index);
}

template <typename T>
bool remove_at(std::vector<T>& v, int index)
{
	if (index < 0 || index >= v.size())
		return false;
	
	v.erase(v.begin() + index);
	
	return true;
}

template <typename T>
bool remove_at(std::vector<T>& v, int from, int to)
{
	if (from > to || from < 0 || from >= v.size() || to < 0 || to >= v.size())
		return false;
	
	v.erase(v.begin() + from, v.begin() + to);
	
	return true;
}

template <typename T>
bool rotate(std::vector<T>& v, int from, int to)
{
	if (from == to)
		return true;
	
	if (from < 0 || from >= v.size() || to < 0 || to >= v.size())
		return false;
	
	if (from > to)
	{
		std::rotate(v.rend() - from - 1, v.rend() - from, v.rend() - to);
	}
	else
	{
		std::rotate(v.begin() + from, v.begin() + from + 1, v.begin() + to + 1);
	}
	
	return true;
}

template <typename T>
int remove_after_index(std::vector<T>& v, int index)
{
	int removed;
	
	if (index >= (int)(v.size() - 1))
	{
		return 0;
	}
	else if (index < 0)
	{
		removed = v.size();
		v.clear();
	}
	else
	{
		removed = v.size() - 1 - index;
		v.erase(v.begin() + index + 1, v.end());
	}
	
	return removed;
}

template <typename T>
void reverse(std::vector<T>& target)
{
	std::reverse(target.begin(), target.end());
}

template <typename T>
void clear(std::vector<T>& a)
{
	std::vector<T> b;
	a.swap(b);
}

template <typename T>
T& last(std::vector<T>& target)
{
	return target[target.size() - 1];
}

template <template<class> class A, class T>
inline size_t sizeof_template(A<T> c) { return sizeof(T); } 

template <template<class, class> class A, class T, class N>
inline size_t sizeof_template(A<T, N> c) { return sizeof(T) + sizeof(N); } 


#endif