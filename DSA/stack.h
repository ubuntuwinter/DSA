// stack.h
#pragma once
#ifndef __STACK_H__
#define __STACK_H__
#include "vector.h"
_DSA_BEGIN
template<typename T>
class Stack : public Vector<T> { // ����������/ĩ����Ϊջ��/��
public:
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); } // ��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } // ��ջ����Ч��ɾ��������ĩԪ��
	T& top() { return (*this)[Vector<T>::size() - 1]; } // ȡ����ֱ�ӷ���������ĩԪ��
};
_DSA_END
#endif // !__STACK_H__
