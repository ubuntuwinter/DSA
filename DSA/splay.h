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

template<typename NodePosi> inline // 在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLChild(NodePosi p, NodePosi lc) {
	p->lc = lc;
	if (lc) lc->parent = p;
}

template<typename NodePosi> inline // 在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRChild(NodePosi p, NodePosi rc) {
	p->rc = rc;
	if (rc) rc->parent = p;
}

template <typename T> // Splay树伸展算法：从节点v出发逐层伸展
BinNodePosi(T) Splay<T>::splay(BinNodePosi(T) v) { // v因最近访问而需伸展的节点位置
	if (!v) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; // *v的父亲和祖父
	while ((p = v->parent) && (g = p->parent)) { // 自下而上，反复对*v做双层伸展
		BinNodePosi(T) gg = g->parent; // 每轮之后*v都以原曾祖父（great-grand parent）为父
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
		if (!gg) v->parent = NULL; // 若*v原先曾祖父*gg不存在，则*v现在应为树根
		else {
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		}
		BinTree<T>::updateHeight(g);
		BinTree<T>::updateHeight(p);
		BinTree<T>::updateHeight(v);
	} // 双层伸展结束时，必有g == NULL，但p可能非空
	if (p = v->parent) { // 若p果真非空，则额外做一次单旋
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
} // 调整之后新树根应为被伸展的节点，故返回该节点的位置以便上层函数更新树根

template<typename T>
BinNodePosi(T)& Splay<T>::search(const T& e) { // 在伸展树中查找e
	BinNodePosi(T) p = searchIn(BinTree<T>::_root, e, BST<T>::_hot = NULL);
	BinTree<T>::_root = splay(p ? p : BST<T>::_hot);
	return BinTree<T>::_root;
} // 与其它BST不同，无论查找成功与否，_root都指向最后被访问的节点


_DSA_END
#endif // !__SPLAY_H__
