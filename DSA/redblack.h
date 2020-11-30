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
_DSA_END
#endif // !__REDBLACK_H__
