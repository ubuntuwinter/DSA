// queue.h
#pragma once
#ifndef __QUEUE_H__
#include "list.h"
_DSA_BEGIN
template<typename T>
class Queue :public List<T> { // ����ģ���ࣨ�̳�Listԭ�нӿڣ�
public:
	void enqueue(T const& e) { List<T>::insertAsLast(e); } // ��ӣ�β������
	T dequeue() { return List<T>::remove(List<T>::first()); } // ���ӣ��ײ�ɾ��
	T& front() { return List<T>::first()->data; } // ����
};
_DSA_END
#endif // !__QUEUE_H__
