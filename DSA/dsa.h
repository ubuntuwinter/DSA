// dsa.h
#pragma once
#ifndef __DSA_H__
#define __DSA_H__
#define _DSA_BEGIN namespace dsa {
#define _DSA_END   }
_DSA_BEGIN
class Fib;
class Bitmap;
template<typename T> class Vector; // ����
template<typename T> struct ListNode; // �б�ڵ�
template<typename T> class List; // �б�
template<typename T> class Stack; // ջ
template<typename T> class Queue; // ����
template<typename T> struct BinNode; // �������ڵ�
template<typename T> class BinTree; // ������
template<typename K, typename B> struct Entry; // ����ģ����
template<typename T> class BST; // ����������
template<typename T> class AVL; // AVL��
template<typename T> struct PQ; // ���ȼ�����
template<typename T> class PQ_ComplHeap; // ��ȫ�����
template<typename T> class PQ_LeftHeap; // ��ʽ��
template<typename Tv, typename Te> class Graph; // ͼ
template<typename Tv, typename Te> class GraphMatrix; // ͼ���ڽӾ���
template<typename Tv, typename Te> class GraphList; // ͼ���ڽӱ�
template<typename T> class Splay; // ��չ��
template<typename T> struct BTNode; // B-���ڵ�
template<typename T> class BTree; // B-��

template<typename T>
void swap(T& a, T& b) { // ����a��b��ֵ
	T c(a);
	a = b;
	b = c;
}

template<typename T>
T max(T const& a, T const& b) {
	return a < b ? b : a;
}

template<typename T>
T min(T const& a, T const& b) {
	return a < b ? a : b;
}

_DSA_END
#endif // !__DSA_H__
