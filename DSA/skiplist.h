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

/*********************************************************************
* Skiplist���������㷨�����ڲ����ã�
* ��ڣ�qlistΪ�����б�pΪqlist�׽ڵ�
* ���ڣ����ɹ���pΪ���йؼ����������Ķ����ڵ㣬qlistΪp�����б�
*		����pΪ�������Ļ�����������Ӧ�ڲ�����k���������ҹؼ��룬qlistΪ��
* Լ���������������ʱ����������ȡ�����
*********************************************************************/
template<typename K, typename V>
bool Skiplist<K, V>::skipSearch(
	ListNode<Quadlist<Entry<K, V>>*>*& qlist, // ��ָ����qlist��
	QuadlistNode<Entry<K, V>>*& p, // �׽ڵ�p����
	K& k) { // ���ҡ����²���Ŀ��ؼ���k
	while (true) { // ��ÿһ��
		while (p->succ && (p->entry.key <= k)) // ��ǰ�������
			p = p->succ; // ֱ�����ָ����key�������trailer
		p = p->pred; // ��ʱ����һ���������ж��Ƿ�
		if (p->pred && (k == p->entry.key)) return true; // ����
		qlist = qlist->succ; // ����ת����һ��
		if (!qlist->succ) return false; // ���Ѵ�͸���ײ㣬����ζ��ʧ��
		p = (p->pred) ? p->below : qlist->data->first(); // ����ת����ǰ������һ�ڵ�
	}
}

template<typename K, typename V>
bool Skiplist<K, V>::put(K, V) { // ��ת����������㷨
	
}

template<typename K, typename V>
V* dsa::Skiplist<K, V>::get(K k) { // ��ת����������㷨
	if (empty()) return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = first(); // �Ӷ���Quadlist��
	QuadlistNode<Entry<K, V>>* q = qlist->data->first(); // �׽ڵ㿪ʼ
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL; // ���Ҳ�����
} // �ж������ʱ����������

_DSA_END
#endif // !__SKIPLIST_H__
