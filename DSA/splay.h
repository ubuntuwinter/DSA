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

template<typename NodePosi> inline // �ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
void attachAsLChild(NodePosi p, NodePosi lc) {
	p->lc = lc;
	if (lc) lc->parent = p;
}

template<typename NodePosi> inline // �ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
void attachAsRChild(NodePosi p, NodePosi rc) {
	p->rc = rc;
	if (rc) rc->parent = p;
}

template <typename T> // Splay����չ�㷨���ӽڵ�v���������չ
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) { // v��������ʶ�����չ�Ľڵ�λ��
	if (!v) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; // *v�ĸ��׺��游
	while ((p = v->parent) && (g = p->parent)) { // ���¶��ϣ�������*v��˫����չ
		BinNodePosi(T) gg = g->parent; // ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ��
		if (IsLChild(*v)) {
			if (IsLChild(*p)) { // zig-zig
				attachAsLChild(g, p->rc); attachAsLChild(p, v->rc);
				attachAsRChild(p, g); attachAsRChild(v, p);
			}
			else { // zig-zag
				attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
				attachAsLChild(v, g); attachAsRChild(v, p);
			}
		}
		else if (IsRChild(*p)) { // zag-zag
			attachAsRChild(g, p->lc); attachAsRChild(p, v->lc);
			attachAsLChild(p, g); attachAsLChild(v, p);
		}
		else { // zag-zig
			attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
			attachAsRChild(v, g); attachAsLChild(v, p);
		}
		if (!gg) v->parent = NULL; // ��*vԭ�����游*gg�����ڣ���*v����ӦΪ����
		else {
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		BinTree<T>::updateHeight(g);
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	} // ˫����չ����ʱ������g == NULL����p���ܷǿ�
	if (p = v->parent) { // ��p����ǿգ��������һ�ε���
		if (IsLChild(*v)) {
			attachAsLChild(p, v->rc);
			attachAsRChild(v, p);
		}
		else {
			attachAsRChild(p, v->lc);
			attachAsLChild(v, p);
		}
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	}
	v->parent = NULL;
	return v;
} // ����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯����������

template<typename T>
BinNodePosi(T)& Splay<T>::search(const T& e) { // ����չ���в���e
	BinNodePosi(T) p = searchIn(BinTree<T>::_root, e, BST<T>::_hot = NULL);
	BinTree<T>::_root = splay(p ? p : BST<T>::_hot);
	return BinTree<T>::_root;
} // ������BST��ͬ�����۲��ҳɹ����_root��ָ����󱻷��ʵĽڵ�

template<typename T>
BinNodePosi(T) Splay<T>::insert(const T& e) { // ���ؼ���e������չ����
	if (!_root) { // ����ԭ��Ϊ�յ��˻����
		BinTree<T>::_size++;
		return _root = new BinNode<T>(e); 
	}
	if (e == search(e)->data) return BinTree<T>::_root; // ȷ��Ŀ��ڵ㲻����
	_size++;
	BinNodePosi(T) t = _root; // �����½ڵ㡣���µ���<=7��ָ������ɾֲ��ع�
	if (BinTree<T>::_root->data < e) { // ������������t��t->rcΪ���Һ���
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t, t->rc); // 2 + 3��
		if (HasRChild(*t)) { // <= 2��
			t->rc->parent = BinTree<T>::_root;
			t->rc = NULL;
		}
	}
	else { // �����¸�����t->lc��tΪ���Һ���
		t->parent = BinTree<T>::_root = new BinNode<T>(e, NULL, t->lc, t); // 2 + 3��
		if (HasLChild(*t)) { // <= 2��
			t->lc->parent = BinTree<T>::_root;
			t->lc = NULL;
		}
	}
	BinTree<T>::updateHeightAbove(t); // ����t�������ȣ�ʵ����ֻ��_rootһ�����ĸ߶�
	return BinTree<T>::_root; // �½ڵ��Ȼ��������������֮
} // ����e�Ƿ������ԭ���У�����ʱ����_root->data == e


_DSA_END
#endif // !__SPLAY_H__
