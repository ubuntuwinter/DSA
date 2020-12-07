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
	int size() const override { return empty ? 0 : last()->data->size(); } // �ײ�Quadlist�Ĺ�ģ
	int level() { return List<Quadlist<Entry<K, V>>*>::size(); } // ��� == #Quadlist, ��һ��Ҫ����
	bool put(K, V) override; // ���루ע����Map�б𡪡�Skiplist��������ظ����ʱ�Ȼ�ɹ���
	V* get(K k) override; // ��ȡ
	bool remove(K k) override; // ɾ��
};
_DSA_END
#endif // !__SKIPLIST_H__
