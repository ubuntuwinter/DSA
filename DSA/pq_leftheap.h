// pq_leftheap.h
#pragma once
#ifndef __PQ_LEFTHEAP_H__
#define __PQ_LEFTHEAP_H__
#include "dsa.h"
#include "pq.h"
#include "binTree.h"
_DSA_BEGIN
template <typename T>
class PQ_LeftHeap :public PQ<T>, public BinTree<T> { // 基于二叉树，以左式堆形式实现的PQ
public:
	PQ_LeftHeap() {} // 默认构造
	PQ_LeftHeap(T* E, int n) { for (int i = 0; i < n; i++) insert(E[i]); } // 批量构造
	void insert(T) override; // 按照比较器大确定的优先级次序插入元素
	T getMax() override; // 取出优先级最高的元素
	T delMax() override; // 删除优先级最高的元素
}; // PQ_LeftHeap

template<typename T> // 根据相对优先级确定适宜的方式，合并以a和b为根的节点
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b) {
	if (!a) return b; // 退化情况
	if (!b) return a; // 退化情况
	if (a->data < b->data) swap(a, b); // 一般情况：首先确定a不小于b
	a->rc = merge(a->rc, b); // 将a的右子堆与b合并
	a->rc->parent = a; // 并更新父子关系
	if (!a->lc || a->lc->npl < a->rc->npl) { // 若有必要
		swap(a->lc, a->rc); // 交换a的左右子堆，以确保右子堆的npl不大于左子堆的npl
	}
	a->npl = a->rc ? a->rc->npl + 1 : 1; // 更新a的npl
	return a; // 返回合并后的堆顶
} // 本算法只实现结构上的合并，堆的规模须由上层调用者负责更新

template<typename T>
void PQ_LeftHeap<T>::insert(T e) { // 基于合并操作的词条插入算法
	BinNodePosi(T) v = new BinNode<T>(e); // 为e创建一个二叉树节点
	BinTree<T>::_root = merge(BinTree<T>::_root, v); // 通过合并完成新节点的插入
	BinTree<T>::_root->parent = NULL; // 既然此时堆非空，还需相应设置父子链接
	BinTree<T>::_size++; // 更新规模
}

template<typename T>
T PQ_LeftHeap<T>::getMax() { // 取出优先级最高的元素
	return BinTree<T>::_root->data;
}

template<typename T>
T PQ_LeftHeap<T>::delMax() { // 基于合并操作的词条删除算法（当前队列非空）
	BinNodePosi(T) lHeap = BinTree<T>::_root->lc; // 左子堆
	BinNodePosi(T) rHeap = BinTree<T>::_root->rc; // 右子堆
	T e = BinTree<T>::_root->data; delete BinTree<T>::_root; BinTree<T>::_size--; // 删除根节点
	BinTree<T>::_root = merge(lHeap, rHeap); // 原左右子堆合并
	if (BinTree<T>::_root) BinTree<T>::_root->parent = NULL; // 若堆非空，还需相应设置父子链接
	return e; // 返回原根节点的数据项
}

_DSA_END
#endif // !__PQ_LEFTHEAP_H__
