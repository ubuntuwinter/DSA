// pq_complheap.h
#pragma once
#ifndef __PQ_COMPLHEAP_H__
#define __PQ_COMPLHEAP_H__
#include "dsa.h"
#include "vector.h"
#include "pq.h"
_DSA_BEGIN
#define InHeap(n, i)		(((-1) < (i)) && ((i) < (n))) // �ж�PQ[i]�Ƿ�Ϸ�
#define Parent(i)			((i - 1) >> 1) // PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define LastInternal(n)		Parent(n - 1) // ���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define LChild(i)			(1 + ((i) << 1)) // PQ[i]������
#define RChild(i)			((1 + (i)) << 1) // PQ[i]���Һ���
#define ParentValid(i)		( 0 < (i)) // �ж�PQ[i]�Ƿ��и���
#define LChildValid(n, i)	InHeap(n, LChild(i)) // �ж�PQ[i]�Ƿ���һ�����󣩺���
#define RChildValid(n, i)	InHeap(n, RChild(i)) // �ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j)	((PQ[i] < PQ[j]) ? j : i) // ȡ���ߣ���ʱǰ�����ȣ�
#define ProperParent(PQ, n, i) /* ���ף����ࣩ�����еĴ��� */ \
			(RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
			(LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i \
			) \
			) // ���ʱ���ڵ����ȣ���˿��Ա��ⲻ��Ҫ�Ľ���

template <typename T> 
class PQ_ComplHeap :public PQ<T>, public Vector<T> { // ��ȫ�����
protected:
	Rank percolateDown(Rank n, Rank i); // ����
	Rank percolateUp(Rank i); // ����
	void heapify(Rank n); // Floyd�����㷨
public:
	PQ_ComplHeap() {} // Ĭ�Ϲ���
	PQ_ComplHeap(T* A, Rank n) { Vector<T>::copyForm(A, 0, n);	heapify(n); } // ��������
	void insert(T) override; // ���ձȽ���ȷ�������ȼ����򣬲������
	T getMax() override; // ��ȡ���ȼ���ߵĴ���
	T delMax() override; // ɾ�����ȼ���ߵĴ���
}; // PQ_ComplHeap

template<typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i) { // ������ǰn�������еĵ�i��ʵʩ���ˣ�i < n 
	Rank j; // i���䣨���������������У���Ϊ����
	while (i != (j = ProperParent(Vector<T>::_elem, n, i))) { // ֻҪi��j����
		swap(Vector<T>::_elem[i], Vector<T>::_elem[j]); i = j; // ���߻�λ�������������½����i
	}
	return i; // �������˵ִ��λ�ã���i��j��
}

template<typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i) { // �������еĵ�i������ʵʩ���˲�����i < Vector<T>::_size
	while (ParentValid(i)) { // ֻҪi�и��ף���δ�ִ�Ѷ�������
		Rank j = Parent(i); // ��i֮����Ϊj
		if (Vector<T>::_elem[i] <= Vector<T>::_elem[j]) break; // һ����ǰ���Ӳ������������������
		swap(Vector<T>::_elem[i], Vector<T>::_elem[j]); i = j; // ���򣬸��ӽ���λ�ã�������������һ��
	} // while
	return i; // �����������յִ��λ��
}

template<typename T>
void PQ_ComplHeap<T>::heapify(Rank n) { // Floyd�����㷨��O(n)ʱ��
	for (int i = LastInternal(n); InHeap(n, i); i--) {
		// �Ե׶��ϣ�����
		percolateDown(n, i); // ���˸��ڲ��ڵ�
	}
}

template<typename T>
void PQ_ComplHeap<T>::insert(T e) { // ������������ȫ�������
	Vector<T>::insert(e); // ���Ƚ��´�����������ĩβ
	percolateUp(Vector<T>::_size - 1); // �ٶԸô���ʵʩ���˵����㷨
}

template<typename T>
T dsa::PQ_ComplHeap<T>::getMax() { // ȡ���ȼ���ߵĴ���
	return Vector<T>::_elem[0];
}

template<typename T>
T PQ_ComplHeap<T>::delMax() { // ɾ���ǿ���ȫ����������ȼ���ߵĴ���
	T maxElem = Vector<T>::_elem[0]; Vector<T>::_elem[0] = Vector<T>::_elem[--Vector<T>::_size]; // ժ���Ѷ����״���������֮��ĩ����
	percolateDown(Vector<T>::_size, 0); // ���¶Ѷ�ʵʩ����
	return maxElem; // ���ش�ǰ���ݵ�������
}

_DSA_END
#endif // !__PQ_COMPLHEAP_H__
