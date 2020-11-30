// redblack.h
#pragma once
#ifndef __REDBLACK_H__
#define __REDBLACK_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color)) // 外部节点也视作黑色
#define IsRed(p) (!IsBlack(p)) // 非黑即红
#define BlackHeightUpdated(x) ( /* RedBlack高度更新条件 */ \
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
	)

template<typename T>
class RedBlack : public BST<T> { // RedBlack树模板类
protected:
	void solveDoubleRed(BinNodePosi(T) x); // 双红修正
	void solveDoubleBlack(BinNodePosi(T) x); // 双黑修正
	int updateHeight(BinNodePosi(T) x) override; // 更新节点x的高度
public:
	BinNodePosi(T) insert(const T& e) override; // 插入（重写）
	bool remove(const T& e) override; // 删除（重写）
	// BST::search()等其余接口可直接沿用
};

/***************************************************************
* RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
*	RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
*	RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
****************************************************************/
template<typename T>
inline void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x) { // x当前必为红
	if (IsRoot(*x)) { // 若已（递归）转至树根，则将其转黑，整数黑高度也随之递增
		BinTree<T>::_root->color = RB_BLACK; BinTree<T>::_root->height++; return;
	} // 否则，x的父亲p必存在
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return; // 若p为黑，则可终止调整。否则
	BinNodePosi(T) g = p->parent; // 既然p为红，则x的祖父必存在，且必为黑色
	BinNodePosi(T) u = uncle(x); // 以下，视x叔父的颜色分别处理
	if (IsBlack(u)) { // u为黑色（含NULL）时
		if (IsLChild(*x) == IsLChild(*p)) { // 若x与p同侧（即zig-zig或zag-zag），则
			p->color = RB_BLACK; // p由红转黑，x保持红
		}
		else { // 若x与p异侧（即zig-zag或zag-zig），则
			x->color = RB_BLACK; // x由红转黑，p保持红
		}
		g->color = RB_RED; // g必定由黑转红
		// 以上虽保证总共两次染色，但因增加了判断而得不偿失
		// 在旋转后将根置黑、孩子置红，随需三次染色但是效率更高
		BinNodePosi(T) gg = g->parent; // 曾祖父（great-grand parent）
		BinNodePosi(T) r = FromParentTo(*g) = BST<T>::rotateAt(x); // 调整后的子树根节点
		r->parent = gg; // 与原曾祖父联接
	}
	else { // 若u为红色
		p->color = RB_BLACK; p->height++; // p由红转黑
		u->color = RB_BLACK; u->height++; // u由红转黑
		if (!IsRoot(*g)) g->color = RB_RED; // g若非根，则转红
		solveDoubleRed(g); // 继续调整g（类似于尾递归，可优化为迭代形式）
	}
}

template<typename T>
int dsa::RedBlack<T>::updateHeight(BinNodePosi(T) x) { // 更新节点高度
	x->height = max(stature(x->lc), stature(x->rc)); // 孩子一般黑高度相等，除非出现双黑
	return IsBlack(x) ? x->height++ : x->height; // 若当前节点为黑，则计入黑深度
} // 因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) { // 将e插入红黑树
	BinNodePosi(T)& x = BST<T>::search(e); if (x) return x; // 确认目标不存在（留意对_hot的设置）
	x = new BinNode<T>(e, BST<T>::_hot, NULL, NULL, -1); BinTree<T>::_size++; // 创建红节点x：以_hot为父，黑高度-1
	solveDoubleRed(x); return x ? x : BST<T>::_hot->parent; // 经双红修正后，即可返回
} // 无论e是否存在于原树中，返回时总有x->data == e

template<typename T>
bool RedBlack<T>::remove(const T& e) { // 从红黑树中删除关键码e
	BinNodePosi(T)& x = search(e); if (!x) return false; // 确认目标存在（留意对_hot的设置）
	BinNodePosi(T) r = removeAt(x, BST<T>::_hot); if (!(--BinTree<T>::_size)) return true; // 实施删除
	// assert：_hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
	if (!_hot) { // 若刚被删除的根节点，则将其置黑，并更新黑高度
		BinTree<T>::_root->color = RB_BLACK; updateHeight(_root); return true;
	}
	// assert：以下，原x（现r）必非根，_hot必非空
	if (BlackHeightUpdated(*_hot)) return true; // 若所有祖先的黑深度依然平衡，则无需调整
	if (IsRed(r)) { // 否则，若r为红，则只需令其转黑
		r->color = RB_BLACK; r->height++; return true;
	}
	// assert：以下，原x（现r）均为黑色
	solveDoubleBlack(r); return true; // 经双黑调整后返回
} // 若目标节点存在且被删除，返回true；否则返回false

_DSA_END
#endif // !__REDBLACK_H__
