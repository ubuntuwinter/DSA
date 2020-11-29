// binNode.h
#pragma once
#ifndef __BINNODE_H__
#define __BINNODE_H__
#include "dsa.h"
#include "queue.h"
#include <cstdlib>
_DSA_BEGIN
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) // 节点高度（与“空树高度为-1”的约定相统一）

/* BinNode状态与性质的判断 */
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) // 至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) // 同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))
/* BinNode状态与性质的判断 */

/* 与BinNode具有特定关系的节点及指针 */
#define sibling(p) /* 兄弟 */ \
(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) /* 叔叔 */ \
(IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc
#define FromParentTo(x) /* 来自父亲的引用 */ \
(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
/* 与BinNode具有特定关系的节点及指针 */

typedef enum { RB_RED, RB_BLACK } RBColor; // 节点颜色

template<typename T>
struct BinNode { // 二叉树节点模板类
	// 成员
	T data; // 数值
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; // 父节点及左、右节点
	int height; // 高度（通用）
	int npl; // Null Path Length（左式堆，也可直接用height代替）
	RBColor color; // 颜色
	// 构造函数
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	// 操作接口
	int size(); // 统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T const& e); // 作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const& e); // 作为当前节点的右孩子插入新节点
	BinNodePosi(T) succ(); // 取当前节点的直接后继
	template<typename VST> void travLevel(VST& visit); // 子树层次遍历
	template<typename VST> void travPre(VST& visit); // 子树先序遍历
	template<typename VST> void travIn(VST& visit); // 子树中序遍历
	template<typename VST> void travPost(VST& visit); // 子树后序遍历
	// 比较器、判等器
	bool operator<(BinNode const& bn) { return data < bn.data; } // 小于
	bool operator==(BinNode const& bn) { return data == bn.data; } // 等于
};

template<typename T>
int BinNode<T>::size() {
	int s = 1; // 计入自己
	if (lc) s += lc->size(); // 递归左子树
	if (rc) s += rc->size(); // 递归右子树
	return s;

}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lc = new BinNode(e, this); // 将e作为当前节点的左孩子插入二叉树
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rc = new BinNode(e, this); // 将e作为当前节点的右孩子插入二叉树
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ() { // 定位节点v的直接后继
	BinNodePosi(T) s = this; // 记录后继的临时变量
	if (rc) { // 若有右孩子，则直接后继必在右子树中，具体地就是
		s = rc; // 右子树中
		while (HasLChild(*s)) s = s->lc; // 最靠左（最小）的节点
	}
	else { // 否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
		while (IsRChild(*s)) s = s->parent; // 逆向地沿右向分支，不断朝左上方移动
		s = s->parent; // 最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit) { // 子树层次遍历算法
	Queue<BinNodePosi(T)> Q; // 辅助队列
	Q.enqueue(this); // 根节点入栈
	while (!Q.empty()) { // 在队列再次变空之前，反复迭代
		BinNodePosi(T) x = Q.dequeue(); visit(x->data); // 取出队首节点并访问之
		if (HasLChild(*x)) Q.enqueue(x->lc); // 左孩子入队
		if (HasRChild(*x)) Q.enqueue(x->rc); // 右孩子入队
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST& visit) { // 子树先序遍历算法
	visit(data);
	if (lc) lc->travPre(visit);
	if (rc) rc->travPre(visit);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travIn(VST& visit) { // 子树中序遍历算法
	if (lc) lc->travIn(visit);
	visit(data);
	if (rc) rc->travIn(visit);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travPost(VST& visit) { // 子树后序遍历算法
	if (lc) lc->travPost(visit);
	if (rc) rc->travPost(visit);
	visit(data);
}

_DSA_END
#endif // !__BINNODE_H__
