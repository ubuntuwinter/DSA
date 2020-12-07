// quadlist.h
#pragma once
#ifndef __QUADLIST_H__
#define __QUADLIST_H__
#include "dsa.h"
#include "quadlistNode.h"
_DSA_BEGIN
template<typename T>
class Quadlist { // Quadlistģ����
private:
	int _size; QlistNodePosi(T) header; QlistNodePosi(T) trailer; // ��ģ��ͷ�ڱ���β�ڱ�
protected:
	void init(); // Quadlist����ʱ�ĳ�ʼ��
	int clear(); // ������нڵ�
public:
	// ���캯��
	Quadlist() { init(); } // Ĭ��
	// ��������
	~Quadlist() { clear(); delete header; delete trailer; } // ɾ�����нڵ㣬�ͷ��ڱ�
	// ֻ�����ʽӿ�
	int size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePosi(T) first() const { return header->succ; }
	QlistNodePosi(T) last() const { return trailer->pred; }
	bool valid(QlistNodePosi(T) p) { // �ж�λ��p�Ƿ����Ϸ�
		return p && (trailer != p) && (header != p);
	}
	// ��д���ʽӿ�
	T remove(QlistNodePosi(T) p); // ɾ�����Ϸ���λ��p���Ľڵ㣬���ر�ɾ���ڵ����ֵ
	QlistNodePosi(T) // ��*e��Ϊp�ĺ�̡�b�����ڲ���
		insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b = NULL);
	// ����
	void traverse(void(*visit)(T&)); // �������ڵ㣬����ʵʩָ������������ָ�룬ֻ����ֲ��޸ģ�
	template<typename VST> // ������
	void traverse(VST& visit); // �������ڵ㣬����ʵʩָ���������������󣬿�ȫ�����޸Ľڵ㣩
};

template<typename T>
void dsa::Quadlist<T>::init() { // Quadlist��ʼ��������Quadlist����ʱͳһ����
	header = new QuadlistNode<T>; // ����ͷ�ڱ��ڵ�
	trailer = new QuadlistNode<T>; // ����β�ڱ��ڵ�
	header->succ = trailer; header->pred = NULL; // �غ��������ڱ�
	trailer->pred = header; trailer->succ = NULL; // �غ��������ڱ�
	header->above = trailer->above = NULL; // ����ĺ���ÿ�
	header->below = trailer->below = NULL; // �����ǰ���ÿ�
	_size = 0; // ��¼��ģ
}

template<typename T>
int Quadlist<T>::clear() { // ���Quadlist
	int oldSize = _size;
	while (0 < _size) remove(header->succ); // ���ɾ�����нڵ�
	return oldSize;
}

template<typename T>
T Quadlist<T>::remove(QlistNodePosi(T) p) { // ɾ��Quadlist��λ��p���Ľڵ㣬�������д�ŵĴ���
	// assert: pΪQuadlist�еĺϷ�λ��
	p->pred->succ = p->succ; p->succ->pred = p->pred; _size--; // ժ���ڵ�
	T e = p->entry; delete p; // ���ݴ������ͷŽڵ�
	return e;
}

template<typename T>
QlistNodePosi(T) Quadlist<T>::insertAfterAbove(T const& e, QlistNodePosi(T) p, QlistNodePosi(T) b) { // ��e��Ϊp�ĺ�̡�b�����ڲ���Quadlist
	_size++; return p->insertAsSuccAbove(e, b); // �����½ڵ�λ�ã�below = NULL��
}

template<typename T>
void Quadlist<T>::traverse(void(*visit)(T&)) {
	for (QlistNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->entry);
}

template<typename T>
template<typename VST>
void Quadlist<T>::traverse(VST& visit) {
	for (QlistNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->entry);
}

_DSA_END
#endif // !__QUADLIST_H__
