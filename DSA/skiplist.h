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
	int size() const override { return List<Quadlist<Entry<K, V>>*>::empty() ? 0 : List<Quadlist<Entry<K, V>>*>::last()->data->size(); } // �ײ�Quadlist�Ĺ�ģ
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
bool Skiplist<K, V>::put(K k, V v) { // ��ת����������㷨
	Entry<K, V> e = Entry<K, V>(k, v); // ������Ĵ�������������ز�����������
	if (List<Quadlist<Entry<K, V>>*>::empty()) List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist<Entry<K, V>>); // �����׸�Entry
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // �Ӷ����������
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // ���׽ڵ����
	if (skipSearch(qlist, p, k)) // �����ʵ��Ĳ���λ��
		while (p->below) p = p->below; // ��������ͬ����������ǿ��ת������
	qlist = List<Quadlist<Entry<K, V>>*>::last(); // ���£�������p���Ҳ࣬һ���������Ե׶����������
	QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p); // �½ڵ�b����������
	while (rand() & 1) { // ��ͶӲ�ң���ȷ��������Ҫ�ٳ���һ�㣬��
		while (qlist->data->valid(p) && !p->above) p = p->pred; // �Ҳ��������ڴ˸߶ȵ����ǰ��
		if (!qlist->data->valid(p)) { // ����ǰ����header
			if (qlist == List<Quadlist<Entry<K, V>>*>::first()) // �ҵ�ǰ������㣬����ζ�ű���
				List<Quadlist<Entry<K, V>>*>::insertAsFirst(new Quadlist <Entry<K, V>>); // ���ȴ����µ�һ�㣬Ȼ��
			p = qlist->pred->data->first()->pred; // ��pת����һ��Skiplist��header
		}
		else { // ���򣬿ɾ�ֱ
			p = p->above; //�������������ø߶�
		}
		qlist = qlist->pred; // ����һ�㣬���ڸò�
		b = qlist->data->insertAfterAbove(e, p, b); // ���½ڵ����p֮��b֮��
	}
	return true; // Dictionary�����ظ�Ԫ�أ��ʲ���سɹ���������Hashtable��Map���в���
}

template<typename K, typename V>
V* Skiplist<K, V>::get(K k) { // ��ת����������㷨
	if (List<Quadlist<Entry<K, V>>*>::empty()) return NULL;
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // �Ӷ���Quadlist��
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // �׽ڵ㿪ʼ
	return skipSearch(qlist, p, k) ? &(p->entry.value) : NULL; // ���Ҳ�����
} // �ж������ʱ����������

template<typename K, typename V>
bool Skiplist<K, V>::remove(K k) { // ��ת�����ɾ���㷨
	if (List<Quadlist<Entry<K, V>>*>::empty()) return false; // �ձ����
	ListNode<Quadlist<Entry<K, V>>*>* qlist = List<Quadlist<Entry<K, V>>*>::first(); // �Ӷ���Quadlist��
	QuadlistNode<Entry<K, V>>* p = qlist->data->first(); // �׽ڵ㿪ʼ
	if (!skipSearch(qlist, p, k)) return false; // Ŀ����������ڣ�ֱ�ӷ���
	do {
		QuadlistNode<Entry<K, V>>* lower = p->below; // ��ס��һ��ڵ㣬��
		qlist->data->remove(p); // ɾ����ǰ��ڵ�
		p = lower; qlist = qlist->succ; // ת����һ��
	} while (qlist->succ); // ���ϲ����ظ���ֱ������
	while (!List<Quadlist<Entry<K, V>>*>::empty() && List<Quadlist<Entry<K, V>>*>::first()->data->empty()) { // ��һ��
		List<Quadlist<Entry<K, V>>*>::remove(List<Quadlist<Entry<K, V>>*>::first()); // ����ѿ��ܲ��������Ķ���Quadlist 
	}
	return true; // ɾ�������ɹ����
}

_DSA_END
#endif // !__SKIPLIST_H__
