// stack.h
#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include "vector.h"
_DSA_BEGIN
template<typename T>
class Stack : public Vector<T> { // 将向量的首/末段作为栈底/顶
public:
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); } // 入栈：等效于将新元素作为向量的末元素插入
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } // 出栈：等效于删除向量的末元素
	T& top() { return (*this)[Vector<T>::size() - 1]; } // 取顶：直接返回向量的末元素
};
_DSA_END
#endif // !__STACK_H__
