// splay.h
#pragma once
#ifndef __SPLAY_H__
#define __SPLAY_H__
#include "dsa.h"
#include "bst.h"
_DSA_BEGIN
template<typename T> 
class Splay :public BST<T> { // ��BST������Splay��ģ����
protected:
	BinNodePosi(T) splay(BinNodePosi(T) v); // ���ڵ�v��չ������
public:
	BinNodePosi(T)& search(const T& e) override; // ���ң���д��
	BinNodePosi(T) insert(const T& e) override; // ���루��д��
	bool remove(const T& e) override; // ɾ������д)
};
_DSA_END
#endif // !__SPLAY_H__
