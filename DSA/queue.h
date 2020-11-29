// queue.h
#pragma once
#ifndef __QUEUE_H__
#include "list.h"
_DSA_BEGIN
template<typename T>
class Queue :public List<T> { // 队列模板类（继承List原有接口）
public:
	void enqueue(T const& e) { List<T>::insertAsLast(e); } // 入队：尾部插入
	T dequeue() { return List<T>::remove(List<T>::first()); } // 出队：首部删除
	T& front() { return List<T>::first()->data; } // 队首
};
_DSA_END
#endif // !__QUEUE_H__
