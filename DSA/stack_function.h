// stack_function.h
#pragma once
#ifndef __STACK_FUNCTION_H__
#define __STACK_FUNCTION_H__
#include "dsa.h"
_DSA_BEGIN
float evaluate(const char* S, char*& RPN); // ����沨�����ʽ
void convert(dsa::Stack<char>& S, __int64 n, int base); // ʮ����������n��base���Ƶ�ת��
bool paren(const char exp[], int lo, int hi); // ���ʽ����ƥ���飬�ɼ����������
void placeQueens(int N); // N�ʺ����⣨�����棩

typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status; // �Թ���Ԫ״̬
// ԭʼ���õġ��ڵ�ǰ·���ϵġ����з��������ʧ�ܻ��ݹ��ġ�����ʹ�õģ�ǽ��

typedef enum { UNKOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN; // ��Ԫ������ڽӷ���
// δ���������ϡ�����������·��ͨ

inline ESWN nextESWN(ESWN eswn); // ����ת����һ�ڽӷ���

struct Cell {
	int x, y; Status status; // x���ꡢy���ꡢ����
	ESWN incoming, outgoing; // ���롢�߳�����
};

inline Cell* neighbor(Cell* cell); // ��ѯ��ǰλ�õ����ڸ��
inline Cell* advance(Cell* cell); // �ӵ�ǰλ��ת�����ڸ��
bool labyinth(Cell** Laby, Cell* s, Cell* t); // �Թ�Ѱ���㷨���ڸ�Ԫs��t֮��滮һ��ͨ·�������ȷ���ڣ�
_DSA_END
#endif // !__STACK_FUNCTION_H__
