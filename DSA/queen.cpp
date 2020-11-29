// queen.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
struct Queen { // 皇后类
	int x, y; // 皇后在棋盘上的位置坐标
	Queen(int xx = 0, int yy = 0) :x(xx), y(yy) {}
	bool operator==(Queen const& q) const { // 重载判等操作符，以检测不同皇后之间可能的冲突
		return (x == q.x) // 行冲突（这一情况其实不会发生，可省略）
			|| (y == q.y) // 列冲突
			|| (x + y == q.x + q.y) // 沿正对角线冲突
			|| (x - y == q.x - q.y); // 沿反对角线冲突
	}
	bool operator!=(Queen const& q) const { return !(*this == q); } // 重载不等操作符
};
void placeQueens(int N) { // N皇后问题（迭代版）：采用试探/回溯的策略，借助栈记录查找的结果
	Stack<Queen> solu; // 存放（部分）解的栈
	Queen q(0, 0); // 从原点出发
	int nCheck = 0, nSolu = 0;
	do {
		if (N <= solu.size() || N <= q.y) { // 若已出界，则
			q = solu.pop(); q.y++; // 回溯一行，并且试探下一列
		}
		else {
			while ((q.y < N) && (0 <= solu.find(q))) { // 通过与已有皇后的比对
					q.y++; nCheck++; // 尝试找到可摆放下一皇后的列
			}
			if (q.y < N) { // 若存在可摆放的列，则
				solu.push(q); // 摆上当前皇后
				if (N <= solu.size()) nSolu++; // 若部分解已成为全局解，则通过变量nSolu计数
				q.x++; q.y = 0; // 转入下一行，从第0列开始，试探下一皇后
			}
		}
	} while ((0 < q.x) || (q.y < N)); // 所有分支均已或穷举或剪枝之后，算法结束
}
_DSA_END