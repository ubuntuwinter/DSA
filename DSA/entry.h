#pragma once
#ifndef __ENTRY_H__
#define __ENTRY_H__
#include "dsa.h"
#include <iostream>
_DSA_BEGIN
template<typename K, typename V>
struct Entry { // 词条模板类
	K key; V value; // 关键码、数值
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // 默认构造函数
	Entry(Entry<K, V> const& e) :key(e.key), value(e.value) {} // 基于克隆的拷贝构造函数
	bool operator<(Entry<K, V> const& e) { return key < e.key; } // 比较器：小于
	bool operator>(Entry<K, V> const& e) { return key > e.key; } // 比较器：大于
	bool operator==(Entry<K, V> const& e) { return key == e.key; } // 判等器：等于
	bool operator!=(Entry<K, V>const& e) { return key != e.key; } // 比较器：不等于
};

template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const Entry<K, V>& entry) {
	out << entry.key << ": " << entry.value;
	return out;
}

_DSA_END
#endif // !__ENTRY_H__
