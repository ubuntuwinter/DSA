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

/***************************************************************
* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
*	RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
*	RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
****************************************************************/
template<typename T>
inline void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x) { // x��ǰ��Ϊ��
	if (IsRoot(*x)) { // ���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
		BinTree<T>::_root->color = RB_BLACK; BinTree<T>::_root->height++; return;
	} // ����x�ĸ���p�ش���
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return; // ��pΪ�ڣ������ֹ����������
	BinNodePosi(T) g = p->parent; // ��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
	BinNodePosi(T) u = uncle(x); // ���£���x�常����ɫ�ֱ���
	if (IsBlack(u)) { // uΪ��ɫ����NULL��ʱ
		if (IsLChild(*x) == IsLChild(*p)) { // ��x��pͬ�ࣨ��zig-zig��zag-zag������
			p->color = RB_BLACK; // p�ɺ�ת�ڣ�x���ֺ�
		}
		else { // ��x��p��ࣨ��zig-zag��zag-zig������
			x->color = RB_BLACK; // x�ɺ�ת�ڣ�p���ֺ�
		}
		g->color = RB_RED; // g�ض��ɺ�ת��
		// �����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
		// ����ת�󽫸��úڡ������ú죬��������Ⱦɫ����Ч�ʸ���
		BinNodePosi(T) gg = g->parent; // ���游��great-grand parent��
		BinNodePosi(T) r = FromParentTo(*g) = BST<T>::rotateAt(x); // ��������������ڵ�
		r->parent = gg; // ��ԭ���游����
	}
	else { // ��uΪ��ɫ
		p->color = RB_BLACK; p->height++; // p�ɺ�ת��
		u->color = RB_BLACK; u->height++; // u�ɺ�ת��
		if (!IsRoot(*g)) g->color = RB_RED; // g���Ǹ�����ת��
		solveDoubleRed(g); // ��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
	}
}

template<typename T>
int dsa::RedBlack<T>::updateHeight(BinNodePosi(T) x) { // ���½ڵ�߶�
	x->height = max(stature(x->lc), stature(x->rc)); // ����һ��ڸ߶���ȣ����ǳ���˫��
	return IsBlack(x) ? x->height++ : x->height; // ����ǰ�ڵ�Ϊ�ڣ����������
} // ��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�

template<typename T>
BinNodePosi(T) RedBlack<T>::insert(const T& e) { // ��e��������
	BinNodePosi(T)& x = BST<T>::search(e); if (x) return x; // ȷ��Ŀ�겻���ڣ������_hot�����ã�
	x = new BinNode<T>(e, BST<T>::_hot, NULL, NULL, -1); BinTree<T>::_size++; // ������ڵ�x����_hotΪ�����ڸ߶�-1
	solveDoubleRed(x); return x ? x : BST<T>::_hot->parent; // ��˫�������󣬼��ɷ���
} // ����e�Ƿ������ԭ���У�����ʱ����x->data == e

template<typename T>
bool RedBlack<T>::remove(const T& e) { // �Ӻ������ɾ���ؼ���e
	BinNodePosi(T)& x = search(e); if (!x) return false; // ȷ��Ŀ����ڣ������_hot�����ã�
	BinNodePosi(T) r = removeAt(x, BST<T>::_hot); if (!(--BinTree<T>::_size)) return true; // ʵʩɾ��
	// assert��_hotĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ����
	if (!_hot) { // ���ձ�ɾ���ĸ��ڵ㣬�����úڣ������ºڸ߶�
		BinTree<T>::_root->color = RB_BLACK; updateHeight(_root); return true;
	}
	// assert�����£�ԭx����r���طǸ���_hot�طǿ�
	if (BlackHeightUpdated(*_hot)) return true; // ���������ȵĺ������Ȼƽ�⣬���������
	if (IsRed(r)) { // ������rΪ�죬��ֻ������ת��
		r->color = RB_BLACK; r->height++; return true;
	}
	// assert�����£�ԭx����r����Ϊ��ɫ
	solveDoubleBlack(r); return true; // ��˫�ڵ����󷵻�
} // ��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false

_DSA_END
#endif // !__REDBLACK_H__
