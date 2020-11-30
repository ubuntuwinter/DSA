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
	void release(BTNodePosi(T) v); // �ͷ����нڵ�
	void solveOverflow(BTNodePosi(T) v); // ����������֮��ķ��Ѵ���
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
void BTree<T>::release(BTNodePosi(T) v) {
	if (!v) return;
	for (int i = 0; i < v->child.size(); i++) {
		release(v->child[i]);
	}
	delete v;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v) { // �ؼ����������ڵ����磬�����ڵ���Ѵ���
	if (_order >= v->child.size()) return; // �ݹ������ǰ�ڵ㲢δ����
	Rank s = _order >> 1; // ��㣨��ʱӦ��_order = key.size() = child.size() - 1��
	BTNodePosi(T) u = new BTNode<T>(); // ע�⣺�½ڵ�����һ���պ���
	for (Rank j = 0; j < _order - s - 1; j++) { // v�Ҳ�_order-s-1�����Ӽ��ؼ������Ϊ�Ҳ�ڵ�
		u->child.insert(j, v->child.remove(s + 1)); // ����ƶ�Ч�ʵ�
		u->key.insert(j, v->key.remove(s + 1)); // �˲��ԿɸĽ�
	}
	u->child[_order - s - 1] = v->child.remove(s + 1); // �ƶ�v��ҵĺ���
	if (u->child[0]) { // ��u�ĺ����Ƿǿգ���
		for (Rank j = 0; j < _order - s; j++) { // �����ǵĸ��ڵ�ͳһ
			u->child[j]->parent = u; // ָ��u
		}
	}
	BTNodePosi(T) p = v->parent; // v��ǰ�ĸ��ڵ�p
	if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; } // ��p���򴴽�֮
	Rank r = 1 + p->key.search(v->key[0]); // p��ָ��u��ָ�����
	p->key.insert(r, v->key.remove(s)); // ���ؼ�������
	p->child.insert(r + 1, u); u->parent = p; // �½ڵ�u�븸�ڵ�p����
	solveOverflow(p); // ����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)��
}

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e) { // ��B-���в��ҹؼ���e
	BTNodePosi(T) v = _root; _hot = NULL; // �Ӹ��ڵ����
	while (v) { // ������
		Rank r = v->key.search(e); // �ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ���
		if ((0 <= r) && (e == v->key[r])) return v; // �ɹ����ڵ�ǰ�ڵ�������Ŀ��ؼ���
		_hot = v; v = v->child[r + 1]; // ����ת���Ӧ������_hotָ���丸����������I/O�����ʱ��
	} // �������������Ƕ��ֲ��ң�����ͨ����_order��ֱ��˳�����
	return NULL; // ʧ�ܣ����յִ��ⲿ�ڵ�
}

template<typename T>
bool BTree<T>::insert(const T& e) { // ���ؼ���e����B����
	BTNodePosi(T) v = search(e); if (v) return false; // ȷ��Ŀ��ڵ㲻����
	Rank r = _hot->key.search(e); // �ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
	_hot->key.insert(r + 1, e); // ���¹ؼ��������Ӧ��λ��
	_hot->child.insert(r + 2, NULL); // ����һ��������ָ��
	_size++; // ����ȫ����ģ
	solveOverflow(_hot); // ���б�Ҫ����������
	return true; // ����ɹ�
}

_DSA_END
#endif // !__BTREE_H__
