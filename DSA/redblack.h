// redblack.h
#pragma once
#ifndef __REDBLACK_H__
#define __REDBLACK_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color)) // �ⲿ�ڵ�Ҳ������ɫ
#define IsRed(p) (!IsBlack(p)) // �Ǻڼ���
#define BlackHeightUpdated(x) ( /* RedBlack�߶ȸ������� */ \
	(stature((x).lc) == stature((x).rc)) && \
	((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)) \
	)

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

template<typename T>
int dsa::RedBlack<T>::updateHeight(BinNodePosi(T) x) { // ���½ڵ�߶�
	x->height = max(stature(x->lc), stature(x->rc)); // ����һ��ڸ߶���ȣ����ǳ���˫��
	return IsBlack(x) ? x->height++ : x->height; // ����ǰ�ڵ�Ϊ�ڣ����������
} // ��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�



_DSA_END
#endif // !__REDBLACK_H__
