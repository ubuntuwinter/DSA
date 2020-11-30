// redblack.h
#pragma once
#ifndef __REDBLACK_H__
#define __REDBLACK_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
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
