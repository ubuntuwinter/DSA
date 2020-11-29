#pragma once
#ifndef __ENTRY_H__
#define __ENTRY_H__
#include "dsa.h"
_DSA_BEGIN
template<typename K, typename V>
struct Entry { // ����ģ����
	K key; V value; // �ؼ��롢��ֵ
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const& e) :key(e.key), value(e.value) {} // ���ڿ�¡�Ŀ������캯��
	bool operator<(Entry<K, V> const& e) { return key < e.key; } // �Ƚ�����С��
	bool operator>(Entry<K, V> const& e) { return key > e.key; } // �Ƚ���������
	bool operator==(Entry<K, V> const& e) { return key == e.key; } // �е���������
	bool operator!=(Entry<K, V>const& e) { return key != e.key; } // �Ƚ�����������
};
_DSA_END
#endif // !__ENTRY_H__
