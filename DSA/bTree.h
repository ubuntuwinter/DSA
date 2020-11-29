// bTree.h
#pragma once
#ifndef __BTREE_H__
#define __BTREE_H__
#include "dsa.h"
#include "btNode.h"
_DSA_BEGIN
template<typename T>
class BTree { // B-��ģ����
protected:
	int _size; // ��ŵĹؼ�������
	int _order; // B-���Ľ״Σ�����Ϊ3��������ʱָ����һ�㲻���޸�
	BTNodePosi(T) _root; // ���ڵ�
	BTNodePosi(T) _hot; // BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ��
	void release(BTNodePosi(T)); // �ͷ����нڵ�
	void solveOverflow(BTNodePosi(T)); // ����������֮��ķ��Ѵ���
	void solveUnderflow(BTNodePosi(T)); // ����������֮��ĺϲ�����
public:
	BTree(int order = 3) :_order(order), _size(0) { // ���캯����Ĭ��Ϊ��͵Ľ�
		_root = new BTNode<T>();
	}
	~BTree() {
		release(_root); // �����������ͷ����нڵ�
	}
	int order() const { return _order; } // �״�
	int size() const { return _size; } // ��ģ
	BTNodePosi(T)& root() { return _root; } // ����
	bool empty() const { return !root; } // �п�
	BTNodePosi(T) search(const T& e); // ����
	bool insert(const T& e); // ����
	bool remove(const T& e); // ɾ��
}; // BTree

template<typename T>
void BTree<T>::release(BTNodePosi(T) p) {
	if (!p) return;
	for (int i = 0; i < p->child.size(); i++) {
		release(p->child[i]);
	}
	delete p;
}

_DSA_END
#endif // !__BTREE_H__
