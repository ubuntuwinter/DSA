// splay.h
#pragma once
#ifndef __SPLAY_H__
#define __SPLAY_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
template<typename T> 
class Splay :public BST<T> { // 由BST派生的Splay树模板类
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v); // 将节点v伸展至树根
public:
	BinNodePosi(T)& search(const T& e) override; // 查找（重写）
	BinNodePosi(T) insert(const T& e) override; // 插入（重写）
	bool remove(const T& e) override; // 删除（重写)
};
_DSA_END
#endif // !__SPLAY_H__
