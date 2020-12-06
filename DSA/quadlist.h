// quadlist.h
#pragma once
#ifndef __QUADLIST_H__
#define __QUADLIST_H__
#include "dsa.h"
#include "quadlistNode.h"
_DSA_BEGIN
template<typename T>
class Quadlist { // Quadlist模板类
private:
	int _size; QlistNodePosi(T) header; QlistNodePosi(T) trailer; // 规模、头哨兵、尾哨兵
protected:
	void init(); // Quadlist创建时的初始化
	int clear(); // 清楚所有节点
public:
	// 构造函数
	Quadlist() { init(); } // 默认
	// 析构函数
	~Quadlist() { clear(); delete header; delete trailer; } // 删除所有节点，释放哨兵
	// 只读访问接口
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePosi(T) first() const { return header->succ; }
	QlistNodePosi(T) last() const { return trailer->pred; }
	bool valid(QlistNodePosi(T) p) { // 判断位置p是否对外合法
		return p && (trailer != p) && (header != p);
	}
	// 可写访问接口
	T remove(QlistNodePosi(T) p); // 删除（合法）位置p处的节点，返回被删除节点的数值
	QlistNodePosi(T) // 将*e作为p的后继、b的上邻插入
		insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL);
	// 遍历
	void traverse((void*)(T&)); // 遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
	template<typename VST> // 操作器
	void traverse(VST&); // 遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
};

template<typename T>
void dsa::Quadlist<T>::init() { // Quadlist初始化，创建Quadlist对象时统一调用
	header = new QuadlistNode<T>; // 创建头哨兵节点
	trailer = new QuadlistNode<T>; // 创建尾哨兵节点
	header->succ = trailer; header->pred = NULL; // 沿横向连接哨兵
	trailer->pred = header; trailer->succ = NULL; // 沿横向连接哨兵
	header->above = trailer->above = NULL; // 纵向的后继置空
	header->below = trailer->below = NULL; // 纵向的前驱置空
	_size = 0; // 记录规模
}

_DSA_END
#endif // !__QUADLIST_H__
