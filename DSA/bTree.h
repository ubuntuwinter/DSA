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

_DSA_END
#endif // !__BTREE_H__
