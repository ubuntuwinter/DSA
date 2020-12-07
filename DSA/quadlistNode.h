// quadlistNode.h
#pragma once
#ifndef __QUADLISTNODE_H__
#define __QUADLISTNODE_H__
#include "dsa.h"
#include <cstdlib>
_DSA_BEGIN
#define QlistNodePosi(T) QuadlistNode<T>* // ��ת��ڵ�λ��

template<typename T>
struct QuadlistNode { // QuadlistNodeģ����
	T entry; // �������
	QlistNodePosi(T) pred; QlistNodePosi(T) succ; // ǰ�������
	QlistNodePosi(T) above; QlistNodePosi(T) below; // ���ڡ�����
	QuadlistNode // ������
	(T e = T(), QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL,
		QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL)
		: entry(e), pred(p), succ(s), above(a), below(b) {}
	QlistNodePosi(T) insertAsSuccAbove // �����½ڵ㣬�Ե�ǰ�ڵ�Ϊǰ�����Խڵ�bΪ����
	(T const& e, QlistNodePosi(T) b = NULL);
};

template<typename T>
QlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const& e, QlistNodePosi(T) b) {
	QlistNodePosi(T) x = new QuadlistNode<T>(e, this, succ, NULL, b);
	succ->pred = x; succ = x; // ����ˮƽ��������
	if (b) b->above = x; // ���ô�ֱ��������
	return x; // �����½ڵ�λ��
}

_DSA_END
#endif // !__QUADLISTNODE_H__
