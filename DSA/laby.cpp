// laby.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
#define LABY_MAX 24; // 最大迷宫尺寸
Cell laby[24][24]; // 迷宫

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); } // 依次转至下一邻接方向

inline Cell* neighbor(Cell* cell) { // 查询当前位置的相邻格点
	switch (cell->outgoing) {
	case EAST:  return cell + LABY_MAX; // 向东
	case SOUTH: return cell + 1;        // 向南
	case WEST:  return cell - LABY_MAX; // 向西
	case NORTH: return cell - 1;        // 向北
	default: exit(-1);
	}
}

inline Cell* advance(Cell* cell) { // 从当前位置转入相邻格点
	Cell* next;
	switch (cell->outgoing) {
	case EAST:  next = cell + LABY_MAX; next->incoming = WEST;  break; // 向东
	case SOUTH: next = cell + 1;        next->incoming = NORTH; break; // 向南
	case WEST:  next = cell - LABY_MAX; next->incoming = EAST;  break; // 向西
	case NORTH: next = cell - 1;        next->incoming = SOUTH; break; // 向北
	default: exit(-1);
	}
	return next;
}

// 迷宫寻径算法：在格单元s至t之间规划一条通路（如果的确存在）
bool labyinth(Cell** Laby, Cell* s, Cell* t) {
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status)) return false; // 退化情况
	Stack<Cell*> path; // 用栈记录通路（Theseus的线绳）
	s->incoming = UNKOWN; s->status = ROUTE; path.push(s); // 起点
	do { // 从起点出发不断试探、回溯，直到抵达终点，或者穷尽所有可能
		Cell* c = path.top(); // 检查当前位置（栈顶)
		if (c == t)return true; // 若已抵达终点，则找到了一条通路；否则，沿尚未试探的方向继续试探
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing))) { // 逐一检查所有方向
			if (AVAILABLE == neighbor(c)->status) break; // 试图找到尚未试探的方向
		}
		if (NO_WAY <= c->outgoing) {// 若所有方向都已尝试过
			c->status = BACKTRACKED;
			c = path.pop(); // 向后回溯一步
		}
		else { // 否则向前试探一步
			path.push(c = advance(c)); c->outgoing = UNKOWN; c->status = ROUTE;
		}
	} while (!path.empty());
	return false;
}

_DSA_END