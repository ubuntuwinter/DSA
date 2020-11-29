// fib.h
#pragma once
#ifndef __FIB_H__
#define __FIB_H__
#include "dsa.h"
_DSA_BEGIN
class Fib { // Fibonacci������
private:
	int f, g; // f = fib(k-1), g = fib(k)
public:
	Fib(int n) // ��ʼ��Ϊ��С��n����СFibonacci��
	{f = 1; g = 0; while (g < n) next(); } // fib(-1)��fib(0)
	int get() { return g; } // ��ȡ��ǰFibonacci��
	int next() { g += f; f = g - f; return g; } // ת����һFibonacci��
	int prev() { f = g - f; g -= f; return g; } // ת����һFibonacci��
};
_DSA_END
#endif // !__FIB_H__
