// avl.h
#pragma once
#ifndef __AVL_H__
#define __AVL_H__
#include "dsa.h"
#include "bst.h" // ����BSTʵ��AVL��
_DSA_BEGIN
#define Balanced(x) (stature((x).lc) == stature((x).rc))// ����ƽ������
#define BalFac(x) (stature((x).lc) - stature((x).rc)) // ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) // AVLƽ������

/* �����Һ�����ȡ������ */
#define tallerChild(x) ( \
	stature((x)->lc) > stature((x)->rc) ? (x)->lc : ( /* ��� */ \
	stature((x)->lc) < stature((x)->rc) ? (x)->rc : ( /* �Ҹ� */ \
	IsLChild(*(x)) ? (x)->lc : (x)->rc /* �ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������ */ \
	) \
	) \
)

template <typename T> class AVL :public BST<T> {  // ��BST������AVL��ģ����
public:
	BinNodePosi(T) insert(const T& e) override; // ���루��д��
	bool remove(const T& e) override; // ɾ������д��
};

template<typename T>
BinNodePosi(T) dsa::AVL<T>::insert(const T& e) { // ���ؼ���e����AVL����
	BinNodePosi(T)& x = BST<T>::search(e); if (x) return x; // ȷ��Ŀ��ڵ㲻����
	BinNodePosi(T) xx = x = new BinNode<T>(e, BST<T>::_hot); BinTree<T>::_size++; // �����½ڵ�x
	// ��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ��
	for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent) { // ��x֮�����ϣ�������������g
		if (!AvlBalanced(*g)) { // һ������gʧ�⣬�򣨲��á�3 + 4"�㷨��ʹ֮���⣬��������
			(IsRoot(*g) ? BinTree<T>::_root : (IsLChild(*g) ? (*g).parent->lc : (*g).parent->rc))
				= BST<T>::rotateAt(tallerChild(tallerChild(g))); // ���½���ԭ��
			break; // g����֮�󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
		}
		else { // ����g��Ȼƽ�⣩��ֻ��򵥵�
			BinTree<T>::updateHeight(g); // ������߶ȣ�ע�⣺��ʹgδʧ�⣬�߶���������ӣ�
		}
	} // ����ֻ��һ�ε�����������������������ȫ����Ȼ��ԭ
	return xx; // �����½ڵ�λ��
} // ����e�Ƿ������ԭ���У�����AVL::insert(e)->data == e

template<typename T>
bool AVL<T>::remove(const T& e) { // ��AVL����ɾ���ؼ���e
	BinNodePosi(T)& x = BST<T>::search(e); if (!x) return false; // ȷ��Ŀ����ڣ�����_hot�����ã�
	removeAt(x, BST<T>::_hot); BinTree<T>::_size--; // �Ȱ�BST����ɾ��֮���˺�ԭ�ڵ�֮��_hot�������Ⱦ�����ʧ�⣩
	for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent) { // ��_hot�������ϣ�������������g
		if (!AvlBalanced(*g)) { // һ������gʧ�⣬�򣨲��á�3 + 4"�㷨��ʹ֮���⣬��������������
			g = (IsRoot(*g) ? BinTree<T>::_root : (IsLChild(*g) ? (*g).parent->lc : (*g).parent->rc))
				= BST<T>::rotateAt(tallerChild(tallerChild(g))); // ԭ����
		}
		BinTree<T>::updateHeight(g); // ��������߶ȣ�ע�⣺��ʹgδʧ�⣬�߶�����ܽ��ͣ�
	} // ��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
	return true; // ɾ���ɹ�
} // ��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false

_DSA_END
#endif // !__AVL_H__
