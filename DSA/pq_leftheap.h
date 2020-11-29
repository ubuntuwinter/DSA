// pq_leftheap.h
#pragma once
#ifndef __PQ_LEFTHEAP_H__
#define __PQ_LEFTHEAP_H__
#include "dsa.h"
#include "pq.h"
#include "binTree.h"
_DSA_BEGIN
template <typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T> { // ���ڶ�����������ʽ����ʽʵ�ֵ�PQ
public:
	PQ_LeftHeap() {} // Ĭ�Ϲ���
	PQ_LeftHeap(T* E, int n) { for (int i = 0; i < n; i++) insert(E[i]); } // ��������
	void insert(T) override; // ���ձȽ�����ȷ�������ȼ��������Ԫ��
	T getMax() override; // ȡ�����ȼ���ߵ�Ԫ��
	T delMax() override; // ɾ�����ȼ���ߵ�Ԫ��
}; // PQ_LeftHeap

template<typename T> // ����������ȼ�ȷ�����˵ķ�ʽ���ϲ���a��bΪ���Ľڵ�
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) {
	if (!a) return b; // �˻����
	if (!b) return a; // �˻����
	if (a->data < b->data) swap(a, b); // һ�����������ȷ��a��С��b
	a->rc = merge(a->rc, b); // ��a�����Ӷ���b�ϲ�
	a->rc->parent = a; // �����¸��ӹ�ϵ
	if (!a->lc || a->lc->npl < a->rc->npl) { // ���б�Ҫ
		swap(a->lc, a->rc); // ����a�������Ӷѣ���ȷ�����Ӷѵ�npl���������Ӷѵ�npl
	}
	a->npl = a->rc ? a->rc->npl + 1 : 1; // ����a��npl
	return a; // ���غϲ���ĶѶ�
} // ���㷨ֻʵ�ֽṹ�ϵĺϲ����ѵĹ�ģ�����ϲ�����߸������

template<typename T>
void PQ_LeftHeap<T>::insert(T e) { // ���ںϲ������Ĵ��������㷨
	BinNodePosi(T) v = new BinNode<T>(e); // Ϊe����һ���������ڵ�
	BinTree<T>::_root = merge(BinTree<T>::_root, v); // ͨ���ϲ�����½ڵ�Ĳ���
	BinTree<T>::_root->parent = NULL; // ��Ȼ��ʱ�ѷǿգ�������Ӧ���ø�������
	BinTree<T>::_size++; // ���¹�ģ
}

template<typename T>
T PQ_LeftHeap<T>::getMax() { // ȡ�����ȼ���ߵ�Ԫ��
	return BinTree<T>::_root->data;
}

template<typename T>
T PQ_LeftHeap<T>::delMax() { // ���ںϲ������Ĵ���ɾ���㷨����ǰ���зǿգ�
	BinNodePosi(T) lHeap = BinTree<T>::_root->lc; // ���Ӷ�
	BinNodePosi(T) rHeap = BinTree<T>::_root->rc; // ���Ӷ�
	T e = BinTree<T>::_root->data; delete BinTree<T>::_root; BinTree<T>::_size--; // ɾ�����ڵ�
	BinTree<T>::_root = merge(lHeap, rHeap); // ԭ�����ӶѺϲ�
	if (BinTree<T>::_root) BinTree<T>::_root->parent = NULL; // ���ѷǿգ�������Ӧ���ø�������
	return e; // ����ԭ���ڵ��������
}

_DSA_END
#endif // !__PQ_LEFTHEAP_H__
