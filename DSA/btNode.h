// btNode.h
#pragma once
#ifndef __BTNODE_H__
#define __BTNODE_H__
#include "dsa.h"
#include "vector.h"
_DSA_BEGIN
#define BTNodePosi(T) BTNode<T>* // B-���ڵ�λ��

template<typename T>
struct BTNode { // B-���ڵ�ģ����
	// ��Ա
	BTNodePosi(T) parent; // ���ڵ�
	Vector<T> key; // �ؼ�������
	Vector<BTNodePosi(T)> child; // �����������䳤���ܱ�key��һ��
	// ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ�룩
	BTNode() { parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL) {
		parent = NULL; // ��Ϊ���ڵ㣬���ҳ�ʼʱ
		key.insert(0, e); // ֻ��һ���ؼ���
		child.insert(0, lc); child.insert(1, rc); // ��������
		if (lc) lc->parent = this; if (rc) rc->parent = this;
	}
};
_DSA_END
#endif // !__BTNODE_H__