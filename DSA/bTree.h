// bTree.h
#pragma once
#ifndef __BTREE_H__
#define __BTREE_H__
#include "dsa.h"
#include "btNode.h"
_DSA_BEGIN
template<typename T>
class BTree { // B-树模板类
protected:
	int _size; // 存放的关键码总数
	int _order; // B-树的阶次，至少为3——创建时指定，一般不能修改
	BTNodePosi(T) _root; // 根节点
	BTNodePosi(T) _hot; // BTree::search()最后访问的非空（除非树空）的节点位置
	void release(BTNodePosi(T)); // 释放所有节点
	void solveOverflow(BTNodePosi(T)); // 因插入而上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T)); // 因插入而下溢之后的合并处理
public:
	BTree(int order = 3) :_order(order), _size(0) { // 构造函数：默认为最低的阶
		_root = new BTNode<T>();
	}
	~BTree() {
		release(_root); // 析构函数：释放所有节点
	}
	int order() const { return _order; } // 阶次
	int size() const { return _size; } // 规模
	BTNodePosi(T)& root() { return _root; } // 树根
	bool empty() const { return !root; } // 判空
	BTNodePosi(T) search(const T& e); // 查找
	bool insert(const T& e); // 插入
	bool remove(const T& e); // 删除
}; // BTree

template<typename T>
void BTree<T>::release(BTNodePosi(T) p) {
	if (!p) return;
	for (int i = 0; i < p->child.size(); i++) {
		release(p->child[i]);
	}
	delete p;
}

template<typename T>
BTNodePosi(T) BTree<T>::search(const T& e) { // 在B-树中查找关键码e
	BTNodePosi(T) v = _root; _hot = NULL; // 从根节点出发
	while (v) { // 逐层查找
		Rank r = v->key.search(e); // 在当前节点中，找到不大于e的最大关键码
		if ((0 <= r) && (e == v->key[r])) return v; // 成功：在当前节点中命中目标关键码
		_hot = v; v = v->child[r + 1]; // 否则，转入对应子树（_hot指向其父）——需做I/O，最费时间
	} // 这里在向量内是二分查找，但对通常的_order可直接顺序查找
	return NULL; // 失败：最终抵达外部节点
}

template<typename T>
bool BTree<T>::insert(const T& e) { // 将关键码e插入B树中
	BTNodePosi(T) v = search(e); if (v) return false; // 确认目标节点不存在
	Rank r = _hot->key.search(e); // 在节点_hot的有序关键码向量中查找合适的插入位置
	_hot->key.insert(r + 1, e); // 将新关键码插至对应的位置
	_hot->child.insert(r + 2, NULL); // 创建一个空子树指针
	_size++; // 更新全树规模
	solveOverflow(_hot); // 如有必要，需做分裂
	return true; // 插入成功
}

_DSA_END
#endif // !__BTREE_H__
