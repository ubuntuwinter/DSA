// binNode.h
#pragma once
#ifndef __BINNODE_H__
#define __BINNODE_H__
#include "dsa.h"
#include "queue.h"
#include <cstdlib>
_DSA_BEGIN
#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) // �ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��

/* BinNode״̬�����ʵ��ж� */
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) // ����ӵ��һ������
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) // ͬʱӵ����������
#define IsLeaf(x) (!HasChild(x))
/* BinNode״̬�����ʵ��ж� */

/* ��BinNode�����ض���ϵ�Ľڵ㼰ָ�� */
#define sibling(p) /* �ֵ� */ \
(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) /* ���� */ \
(IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc
#define FromParentTo(x) /* ���Ը��׵����� */ \
(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
/* ��BinNode�����ض���ϵ�Ľڵ㼰ָ�� */

typedef enum { RB_RED, RB_BLACK } RBColor; // �ڵ���ɫ

template<typename T>
struct BinNode { // �������ڵ�ģ����
	// ��Ա
	T data; // ��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; // ���ڵ㼰���ҽڵ�
	int height; // �߶ȣ�ͨ�ã�
	int npl; // Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; // ��ɫ
	// ���캯��
	BinNode() :parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	// �����ӿ�
	int size(); // ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNodePosi(T) insertAsLC(T const& e); // ��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const& e); // ��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T) succ(); // ȡ��ǰ�ڵ��ֱ�Ӻ��
	template<typename VST> void travLevel(VST& visit); // ������α���
	template<typename VST> void travPre(VST& visit); // �����������
	template<typename VST> void travIn(VST& visit); // �����������
	template<typename VST> void travPost(VST& visit); // �����������
	// �Ƚ������е���
	bool operator<(BinNode const& bn) { return data < bn.data; } // С��
	bool operator==(BinNode const& bn) { return data == bn.data; } // ����
};

template<typename T>
int BinNode<T>::size() {
	int s = 1; // �����Լ�
	if (lc) s += lc->size(); // �ݹ�������
	if (rc) s += rc->size(); // �ݹ�������
	return s;

}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e) {
	return lc = new BinNode(e, this); // ��e��Ϊ��ǰ�ڵ�����Ӳ��������
}

template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e) {
	return rc = new BinNode(e, this); // ��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
}

template<typename T>
BinNodePosi(T) BinNode<T>::succ() { // ��λ�ڵ�v��ֱ�Ӻ��
	BinNodePosi(T) s = this; // ��¼��̵���ʱ����
	if (rc) { // �����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
		s = rc; // ��������
		while (HasLChild(*s)) s = s->lc; // �����С���Ľڵ�
	}
	else { // ����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
		while (IsRChild(*s)) s = s->parent; // ������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; // ����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit) { // ������α����㷨
	Queue<BinNodePosi(T)> Q; // ��������
	Q.enqueue(this); // ���ڵ���ջ
	while (!Q.empty()) { // �ڶ����ٴα��֮ǰ����������
		BinNodePosi(T) x = Q.dequeue(); visit(x->data); // ȡ�����׽ڵ㲢����֮
		if (HasLChild(*x)) Q.enqueue(x->lc); // �������
		if (HasRChild(*x)) Q.enqueue(x->rc); // �Һ������
	}
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST& visit) { // ������������㷨
	visit(data);
	if (lc) lc->travPre(visit);
	if (rc) rc->travPre(visit);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travIn(VST& visit) { // ������������㷨
	if (lc) lc->travIn(visit);
	visit(data);
	if (rc) rc->travIn(visit);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travPost(VST& visit) { // ������������㷨
	if (lc) lc->travPost(visit);
	if (rc) rc->travPost(visit);
	visit(data);
}

_DSA_END
#endif // !__BINNODE_H__
