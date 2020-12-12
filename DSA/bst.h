// bst.h
#pragma once
#ifndef _BST_H__
#define _BST_H__
#include "dsa.h"
#include "binTree.h"
_DSA_BEGIN
template <typename T>
class BST : public BinTree<T> { // ��BinTree����BSTģ����
protected:
	BinNodePosi(T) _hot; // �����С��ڵ�ĸ���
	BinNodePosi(T) connect34( // ���ա�3+4���ṹ������3���ڵ㼰�Ŀ�����
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3);
	BinNodePosi(T) rotateAt(BinNodePosi(T) v); // ��x���丸�ס��游��ͳһ��ת����
public: // �����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
	virtual BinNodePosi(T)& search(const T& e); // ����
	virtual BinNodePosi(T) insert(const T& e); // ����
	virtual bool remove(const T& e); // ɾ��
};

template<typename T> // ����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data)) return v; // �ݹ�����ڽڵ�v��������ͨ��ڵ㴦���У�
	hot = v; // һ��������ȼ��µ�ǰ�ڵ㣬Ȼ����
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot); // ����һ�㣬�ݹ����
} // ����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = x; // ʵ�ʱ�ժ���Ľڵ�
	BinNodePosi(T) succ = NULL; // ʵ�ʱ�ɾ���ڵ�Ľ�����
	if (!HasLChild(*x)) { // ��*x��������Ϊ�գ����
		succ = x = x->rc; // ֱ�ӽ�*x�滻Ϊ��������
	}
	else if (!HasRChild(*x)) { // ��*x��������Ϊ�գ����
		succ = x = x->lc; // ֱ�ӽ�*x�滻Ϊ�����������ԳƵش�����ע�⣺��ʱsucc != NULL
	}
	else { // ���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
		w = w->succ();
		swap(x->data, w->data); // ����*x��*w������Ԫ��
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc; // ����ڵ�*w
	}
	hot = w->parent; // ��¼ʵ�ʱ�ɾ���ڵ�ĸ���
	if (succ) succ->parent = hot; // ������ɾ���ڵ�Ľ�������hot����
	delete w; return succ; // �ͷű�ժ���ڵ㣬���ؽ�����
}

template<typename T> // ���ա�3+4���ṹ������3���ڵ㼰�Ŀ�����
BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3) {
	a->lc = T0; if (T0) T0->parent = a;
	a->rc = T1; if (T1) T1->parent = a; BinTree<T>::updateHeight(a);
	c->lc = T2; if (T2) T2->parent = c;
	c->rc = T3; if (T3) T3->parent = c; BinTree<T>::updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; BinTree<T>::updateHeight(b);
	return b; // �������µĸ��ڵ�
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) { // vΪ�ǿ��ﱲ�ڵ�
	BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; // ��v��p��g�����λ�÷��������
	if (IsLChild(*p)) {/* zig */
		if (IsLChild(*v)) { /* zig-zig */
			p->parent = g->parent; // ��������
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else { /* zig-zag */
			v->parent = g->parent; // ��������
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else { /* zag */
		if (IsRChild(*v)) { /* zag-zag */
			p->parent = g->parent; // ��������
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else { /* zag-zig */
			v->parent = g->parent; // ��������
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}
}

template<typename T>
BinNodePosi(T)& BST<T>::search(const T& e) { // ��BST�в��ҹؼ���e
	return searchIn(BinTree<T>::_root, e, _hot = NULL);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T& e) { // ���ؼ���e����BST����
	BinNodePosi(T)& x = search(e);  if (x) return x;// ȷ��Ŀ�겻����
	x = new BinNode<T>(e, _hot); // �����½ڵ�x����eΪ�ؼ��룬��_hotΪ��
	BinTree<T>::_size++; // ����ȫ����ģ
	BinTree<T>::updateHeightAbove(_hot); // ����x�����������ȵĸ߶�
	return x; // �²���Ľڵ㣬��ΪҶ��
} // ����e�Ƿ������ԭ���У�����ʱ����x->data == e

template<typename T>
bool BST<T>::remove(const T& e) { // ��BST����ɾ���ؼ���e
	BinNodePosi(T)& x = search(e); if (!x) return false; // ȷ��Ŀ����ڣ�����_hot�����ã�
	removeAt(x, _hot); BinTree<T>::_size--; // ʵʩɾ��
	BinTree<T>::updateHeightAbove(_hot); // ����_hot�����������ȵĸ߶�
	return true;
} // ɾ���ɹ�����ɷ���ֵָʾ

_DSA_END
#endif // !_BST_H__
