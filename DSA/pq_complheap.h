// pq_complheap.h
#pragma once
#ifndef __PQ_COMPLHEAP_H__
#define __PQ_COMPLHEAP_H__
#include "dsa.h"
#include "vector.h"
#include "pq.h"
_DSA_BEGIN
#define InHeap(n, i)		(((-1) < (i)) && ((i) < (n))) // 判断PQ[i]是否合法
#define Parent(i)			((i - 1) >> 1) // PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define LastInternal(n)		Parent(n - 1) // 最后一个内部节点（即末节点的父亲）
#define LChild(i)			(1 + ((i) << 1)) // PQ[i]的左孩子
#define RChild(i)			((1 + (i)) << 1) // PQ[i]的右孩子
#define ParentValid(i)		( 0 < (i)) // 判断PQ[i]是否有父亲
#define LChildValid(n, i)	InHeap(n, LChild(i)) // 判断PQ[i]是否有一个（左）孩子
#define RChildValid(n, i)	InHeap(n, RChild(i)) // 判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j)	((PQ[i] < PQ[j]) ? j : i) // 取大者（等时前者优先）
#define ProperParent(PQ, n, i) /* 父亲（至多）三者中的大者 */ \
			(RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
			(LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i \
			) \
			) // 相等时父节点优先，如此可以避免不必要的交换

template <typename T> 
class PQ_ComplHeap :public PQ<T>, public Vector<T> { // 完全二叉堆
protected:
	Rank percolateDown(Rank n, Rank i); // 下滤
	Rank percolateUp(Rank i); // 上滤
	void heapify(Rank n); // Floyd建堆算法
public:
	PQ_ComplHeap() {} // 默认构造
	PQ_ComplHeap(T* A, Rank n) { Vector<T>::copyForm(A, 0, n);	heapify(n); } // 批量构造
	void insert(T) override; // 按照比较器确定的优先级次序，插入词条
	T getMax() override; // 读取优先级最高的词条
	T delMax() override; // 删除优先级最高的词条
}; // PQ_ComplHeap

template<typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) { // 对向量前n个词条中的第i个实施下滤，i < n 
	Rank j; // i及其（至多两个）孩子中，堪为父者
	while (i != (j = ProperParent(Vector<T>::_elem, n, i))) { // 只要i非j，则
		swap(Vector<T>::_elem[i], Vector<T>::_elem[j]); i = j; // 二者换位，并继续考察下降后的i
	}
	return i; // 返回下滤抵达的位置（亦i亦j）
}

template<typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i) { // 对向量中的第i个词条实施上滤操作，i < Vector<T>::_size
	while (ParentValid(i)) { // 只要i有父亲（尚未抵达堆顶），则
		Rank j = Parent(i); // 将i之父记为j
		if (Vector<T>::_elem[i] <= Vector<T>::_elem[j]) break; // 一旦当前父子不再逆序，上滤旋即完成
		swap(Vector<T>::_elem[i], Vector<T>::_elem[j]); i = j; // 否则，父子交换位置，并继续考查上一层
	} // while
	return i; // 返回上滤最终抵达的位置
}

template<typename T>
void PQ_ComplHeap<T>::heapify(Rank n) { // Floyd建堆算法，O(n)时间
	for (int i = LastInternal(n); InHeap(n, i); i--) {
		// 自底而上，依次
		percolateDown(n, i); // 下滤各内部节点
	}
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e) { // 将词条插入完全二叉堆中
	Vector<T>::insert(e); // 首先将新词条接至向量末尾
	percolateUp(Vector<T>::_size - 1); // 再对该词条实施上滤调整算法
}

template<typename T>
T dsa::PQ_ComplHeap<T>::getMax() { // 取优先级最高的词条
	return Vector<T>::_elem[0];
}

template<typename T>
T PQ_ComplHeap<T>::delMax() { // 删除非空完全二叉堆中优先级最高的词条
	T maxElem = Vector<T>::_elem[0]; Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size]; // 摘除堆顶（首词条），代之以末词条
	percolateDown(Vector<T>::_size, 0); // 对新堆顶实施下滤
	return maxElem; // 返回此前备份的最大词条
}

_DSA_END
#endif // !__PQ_COMPLHEAP_H__
