// skiplist.h
#pragma once
#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__
#include "dsa.h"
#include "list.h"
#include "entry.h"
#include "quadlist.h"
#include "dictionary.h"
_DSA_BEGIN
template<typename K, typename V> // key, value
class Skiplist :public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*> {
protected:
	bool skipSearch(
		ListNode<Quadlist<Entry<K, V>>*>*& qlist,
		QuadlistNode<Entry<K, V>>*& p,
		K& k);
public:
	int size() const override { return empty ? 0 : last()->data->size(); } // 底层Quadlist的规模
	int level() { return List<Quadlist<Entry<K, V>>*>::size(); } // 层高 == #Quadlist, 不一定要开放
	bool put(K, V) override; // 插入（注意与Map有别——Skiplist允许词条重复，故必然成功）
	V* get(K k) override; // 读取
	bool remove(K k) override; // 删除
};
_DSA_END
#endif // !__SKIPLIST_H__
