// redblack.h
#pragma once
#ifndef __REDBLACK_H__
#define __REDBLACK_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
template<typename T>
class RedBlack : public BST<T> { // RedBlack��ģ����
protected:
	void solveDoubleRed(BinNodePosi(T) x); // ˫������
	void solveDoubleBlack(BinNodePosi(T) x); // ˫������
	int updateHeight(BinNodePosi(T) x) override; // ���½ڵ�x�ĸ߶�
public:
	BinNodePosi(T) insert(const T& e) override; // ���루��д��
	bool remove(const T& e) override; // ɾ������д��
	// BST::search()������ӿڿ�ֱ������
};
_DSA_END
#endif // !__REDBLACK_H__
