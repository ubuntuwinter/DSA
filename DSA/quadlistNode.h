// quadlistNode.h
#pragma once
#ifndef __QUADLISTNODE_H__
#define __QUADLISTNODE_H__
#include "dsa.h"
#include <cstdlib>
_DSA_BEGIN
#define QlistNodePosi(T) QuadlistNode<T>* // 跳转表节点位置

template<typename T>
struct QuadlistNode { // QuadlistNode模板类
	T entry; // 所存词条
	QlistNodePosi(T) pred; QlistNodePosi(T) succ; // 前驱、后继
	QlistNodePosi(T) above; QlistNodePosi(T) below; // 上邻、下邻
	QuadlistNode // 构造器
	(T e = T(), QlistNodePosi(T) p = NULL, QlistNodePosi(T) s = NULL,
		QlistNodePosi(T) a = NULL, QlistNodePosi(T) b = NULL)
		: entry(e), pred(p), succ(s), above(a), below(b) {}
	QlistNodePosi(T) insertAsSuccAbove // 插入新节点，以当前节点为前驱，以节点b为下邻
	(T const& e, QlistNodePosi(T) b = NULL);
};

template<typename T>
QlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const& e, QlistNodePosi(T) b) {
	QlistNodePosi(T) x = new QuadlistNode<T>(e, this, succ, NULL, b);
	succ->pred = x; succ = x; // 设置水平逆向连接
	if (b) b->above = x; // 设置垂直逆向连接
	return x; // 返回新节点位置
}

_DSA_END
#endif // !__QUADLISTNODE_H__
