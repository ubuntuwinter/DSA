// laby.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
#define LABY_MAX 24; // ����Թ��ߴ�
Cell laby[24][24]; // �Թ�

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); } // ����ת����һ�ڽӷ���

inline Cell* neighbor(Cell* cell) { // ��ѯ��ǰλ�õ����ڸ��
	switch (cell->outgoing) {
	case EAST:  return cell + LABY_MAX; // ��
	case SOUTH: return cell + 1;        // ����
	case WEST:  return cell - LABY_MAX; // ����
	case NORTH: return cell - 1;        // ��
	default: exit(-1);
	}
}

inline Cell* advance(Cell* cell) { // �ӵ�ǰλ��ת�����ڸ��
	Cell* next;
	switch (cell->outgoing) {
	case EAST:  next = cell + LABY_MAX; next->incoming = WEST;  break; // ��
	case SOUTH: next = cell + 1;        next->incoming = NORTH; break; // ����
	case WEST:  next = cell - LABY_MAX; next->incoming = EAST;  break; // ����
	case NORTH: next = cell - 1;        next->incoming = SOUTH; break; // ��
	default: exit(-1);
	}
	return next;
}

// �Թ�Ѱ���㷨���ڸ�Ԫs��t֮��滮һ��ͨ·�������ȷ���ڣ�
bool labyinth(Cell** Laby, Cell* s, Cell* t) {
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false; // �˻����
	Stack<Cell*> path; // ��ջ��¼ͨ·��Theseus��������
	s->incoming = UNKOWN; s->status = ROUTE; path.push(s); // ���
	do { // ��������������̽�����ݣ�ֱ���ִ��յ㣬��������п���
		Cell* c = path.top(); // ��鵱ǰλ�ã�ջ��)
		if (c == t)return true; // ���ѵִ��յ㣬���ҵ���һ��ͨ·����������δ��̽�ķ��������̽
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) { // ��һ������з���
			if (AVAILABLE == neighbor(c)->status) break; // ��ͼ�ҵ���δ��̽�ķ���
		}
		if (NO_WAY <= c->outgoing) {// �����з����ѳ��Թ�
			c->status = BACKTRACKED;
			c = path.pop(); // ������һ��
		}
		else { // ������ǰ��̽һ��
			path.push(c = advance(c)); c->outgoing = UNKOWN; c->status = ROUTE;
		}
	} while (!path.empty());
	return false;
}

_DSA_END