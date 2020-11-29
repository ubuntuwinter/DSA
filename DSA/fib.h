// fib.h
#pragma once
#ifndef __FIB_H__
#define __FIB_H__
#include "dsa.h"
_DSA_BEGIN
class Fib { // Fibonacci数列类
private:
	int f, g; // f = fib(k-1), g = fib(k)
public:
	Fib(int n) // 初始化为不小于n的最小Fibonacci项
	{f = 1; g = 0; while (g < n) next(); } // fib(-1)，fib(0)
	int get() { return g; } // 获取当前Fibonacci项
	int next() { g += f; f = g - f; return g; } // 转至下一Fibonacci项
	int prev() { f = g - f; g -= f; return g; } // 转至上一Fibonacci项
};
_DSA_END
#endif // !__FIB_H__
