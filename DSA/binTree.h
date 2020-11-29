// binTree.h
#pragma once
#ifndef __BINTREE_H__
#define __BINTREE_H__
#include "dsa.h"
#include "binNode.h" // ����������ڵ���
_DSA_BEGIN
template<typename T>
class BinTree { // ������ģ����
protected:
	int _size; BinNodePosi(T) _root; // ��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi(T) x); // ���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x); // ���½ڵ�x��������ĸ߶�
public:
	BinTree() : _size(0), _root(NULL) {} // ���캯��
	~BinTree() { if (0 < _size) remove(_root); } // ��������
	int size() const { return _size; } // ��ģ
	bool empty() const { return !_root; } // �п�
	BinNodePosi(T) root() const { return _root; } // ����
	BinNodePosi(T) insertAsRoot(T const& e); // ������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); // e��Ϊx�����ӣ�ԭ�ޣ�����
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); // e��Ϊx���Һ��ӣ�ԭ�ޣ�����
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& S); // T��Ϊx����������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& S); // T��Ϊx����������
	int remove(BinNodePosi(T) x); // ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x); // ������x�ӵ�ǰ����ժ����������ת��Ϊһ�Ŷ�������
	template<typename VST> // ������
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } // ��α���
	template<typename VST> // ������
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } // �������
	template<typename VST> // ������
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } // �������
	template<typename VST> // ������
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } // �������
	bool operator<(BinTree<T> const& t) //�Ƚ���
	{
		return _root && t._root && _root < t._root;
	}
	bool operator==(BinTree<T> const& t) // �е���
	{
		return _root && t._root && _root == t.root;
	}
}; // BinTree

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) { // ���½ڵ�x�߶�
	return x->height = 1 + max(stature(x->lc), stature(x->rc)); // ���������������
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) { // ���¸߶�
	while (x) { updateHeight(x); x = x->parent; } // ��x������������������
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) { // ��e�������ڵ����յĶ�����
	_size = 1; return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) { // e����Ϊx������
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) { // e��Ϊx���Һ��Ӳ���
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;
}

template<typename T> // �����������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>*& S) { // x->lc == NULL
	if (x->lc = S->_root) x->lc->parent = x;// ����
	_size += S->_size; updateHeightAbove(x); // ����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; delete S; S = NULL; return x; // �ͷ�ԭ�������ؽ���λ��
}

template<typename T> // �����������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>*& S) { // x->rc == NULL
	if (x->rc = S->_root) x->rc->parent = x;// ����
	_size += S->_size; updateHeightAbove(x); // ����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; delete S; S = NULL; return x; // �ͷ�ԭ�������ؽ���λ��
}

template<typename T> // ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T) x) { // assert: xΪ�������кϷ�λ��
	if (!x) return 0; // �ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc); // �ݹ��ͷ���������
	delete x; return n; // �ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}

template<typename T> // ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T) x) { // assert: xΪ�������еĺϷ�λ��
	FromParentTo(*x) = NULL; // �ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); // �������ȸ߶�
	int n = removeAt(x); _size -= n; return n; // ɾ������x�����¹�ģ������ɾ���ڵ�����
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL; // �ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); // ����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; // ������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; // ���¹�ģ�����ط������������
}



_DSA_END
#endif // !__BINTREE_H__
