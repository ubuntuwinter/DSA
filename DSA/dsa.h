// dsa.h
#pragma once
#ifndef __DSA_H__
#define __DSA_H__
#define _DSA_BEGIN namespace dsa {
#define _DSA_END   }
_DSA_BEGIN
class Fib;
class Bitmap;
template<typename T> class Vector; // 向量
template<typename T> struct ListNode; // 列表节点
template<typename T> class List; // 列表
template<typename T> class Stack; // 栈
template<typename T> class Queue; // 队列
template<typename T> struct BinNode; // 二叉树节点
template<typename T> class BinTree; // 二叉树
template<typename K, typename B> struct Entry; // 词条模板类
template<typename T> class BST; // 二叉搜索树
template<typename T> class AVL; // AVL树
template<typename T> struct PQ; // 优先级队列
template<typename T> class PQ_ComplHeap; // 完全二叉堆
template<typename T> class PQ_LeftHeap; // 左式堆
template<typename Tv, typename Te> class Graph; // 图
template<typename Tv, typename Te> class GraphMatrix; // 图：邻接矩阵
template<typename Tv, typename Te> class GraphList; // 图：邻接表
template<typename T> class Splay; // 伸展树
template<typename T> struct BTNode; // B-树节点
template<typename T> class BTree; // B-树

template<typename T>
void swap(T& a, T& b) { // 交换a和b的值
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
