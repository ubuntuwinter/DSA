// stack_function.h
#pragma once
#ifndef __STACK_FUNCTION_H__
#define __STACK_FUNCTION_H__
#include "dsa.h"
_DSA_BEGIN
float evaluate(const char* S, char*& RPN); // 求解逆波兰表达式
void convert(dsa::Stack<char>& S, __int64 n, int base); // 十进制正整数n到base进制的转换
bool paren(const char exp[], int lo, int hi); // 表达式括号匹配检查，可兼顾三种括号
void placeQueens(int N); // N皇后问题（迭代版）

typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status; // 迷宫单元状态
// 原始可用的、在当前路径上的、所有方向均尝试失败回溯过的、不可使用的（墙）

typedef enum { UNKOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN; // 单元的相对邻接方向
// 未定、东、南、西、北、无路可通

inline ESWN nextESWN(ESWN eswn); // 依次转至下一邻接方向

struct Cell {
	int x, y; Status status; // x坐标、y坐标、类型
	ESWN incoming, outgoing; // 进入、走出方向
};

inline Cell* neighbor(Cell* cell); // 查询当前位置的相邻格点
inline Cell* advance(Cell* cell); // 从当前位置转入相邻格点
bool labyinth(Cell** Laby, Cell* s, Cell* t); // 迷宫寻径算法：在格单元s至t之间规划一条通路（如果的确存在）
_DSA_END
#endif // !__STACK_FUNCTION_H__
