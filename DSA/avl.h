// avl.h
#pragma once
#ifndef __AVL_H__
#define __AVL_H__
#include "dsa.h"
#include "bst.h" // 基于BST实现AVL树
_DSA_BEGIN
#define Balanced(x) (stature((x).lc) == stature((x).rc))// 理想平衡条件
#define BalFac(x) (stature((x).lc) - stature((x).rc)) // 平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) // AVL平衡条件

/* 在左、右孩子中取更高者 */
#define tallerChild(x) ( \
	stature((x)->lc) > stature((x)->rc) ? (x)->lc : ( /* 左高 */ \
	stature((x)->lc) < stature((x)->rc) ? (x)->rc : ( /* 右高 */ \
	IsLChild(*(x)) ? (x)->lc : (x)->rc /* 等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先 */ \
	) \
	) \
)

template <typename T> class AVL :public BST<T> {  // 由BST树派生AVL树模板类
public:
	BinNodePosi(T) insert(const T& e) override; // 插入（重写）
	bool remove(const T& e) override; // 删除（重写）
};

template<typename T>
BinNodePosi(T) dsa::AVL<T>::insert(const T& e) { // 将关键码e插入AVL树中
	BinNodePosi(T)& x = BST<T>::search(e); if (x) return x; // 确认目标节点不存在
	BinNodePosi(T) xx = x = new BinNode<T>(e, BST<T>::_hot); BinTree<T>::_size++; // 创建新节点x
	// 此时，x的父亲_hot若增高，则其祖父有可能失衡
	for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent) { // 从x之父向上，逐层检查各代祖先g
		if (!AvlBalanced(*g)) { // 一旦发现g失衡，则（采用“3 + 4"算法）使之复衡，并将子树
			(IsRoot(*g) ? BinTree<T>::_root : (IsLChild(*g) ? (*g).parent->lc : (*g).parent->rc))
				= BST<T>::rotateAt(tallerChild(tallerChild(g))); // 重新接入原树
			break; // g复衡之后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
		}
		else { // 否则（g依然平衡），只需简单地
			BinTree<T>::updateHeight(g); // 更新其高度（注意：即使g未失衡，高度亦可能增加）
		}
	} // 至多只需一次调整；若果真做过调整，则全树必然复原
	return xx; // 返回新节点位置
} // 无论e是否存在于原树中，总有AVL::insert(e)->data == e

template<typename T>
bool AVL<T>::remove(const T& e) { // 从AVL树中删除关键码e
	BinNodePosi(T)& x = BST<T>::search(e); if (!x) return false; // 确认目标存在（留意_hot的设置）
	removeAt(x, BST<T>::_hot); BinTree<T>::_size--; // 先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
	for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent) { // 从_hot出发向上，逐层检查各代祖先g
		if (!AvlBalanced(*g)) { // 一旦发现g失衡，则（采用“3 + 4"算法）使之复衡，并将该子树联至
			g = (IsRoot(*g) ? BinTree<T>::_root : (IsLChild(*g) ? (*g).parent->lc : (*g).parent->rc))
				= BST<T>::rotateAt(tallerChild(tallerChild(g))); // 原父亲
		}
		BinTree<T>::updateHeight(g); // 并更新其高度（注意：即使g未失衡，高度亦可能降低）
	} // 可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
	return true; // 删除成功
} // 若目标节点存在且被删除，返回true；否则返回false

_DSA_END
#endif // !__AVL_H__
