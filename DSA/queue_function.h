// queue_function.h
#pragma once
#ifndef __QUEUE_FUNCTION_H__
#define __QUEUE_FUNCTION_H__
#include "dsa.h"
_DSA_BEGIN
struct Customer { int window; unsigned int time; }; // 顾客类：所属窗口（队列)、服务时长
void simulate(int nWin, int servTime); // 按指定窗口数、服务总时间模拟银行业务
int bestWindow(Queue<Customer> windows[], int nWin); // 为新到顾客确定最佳队列
_DSA_END
#endif // !__QUEUE_FUNCTION_H__
