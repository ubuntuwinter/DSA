// queue_function.h
#pragma once
#ifndef __QUEUE_FUNCTION_H__
#define __QUEUE_FUNCTION_H__
#include "dsa.h"
_DSA_BEGIN
struct Customer { int window; unsigned int time; }; // �˿��ࣺ�������ڣ�����)������ʱ��
void simulate(int nWin, int servTime); // ��ָ����������������ʱ��ģ������ҵ��
int bestWindow(Queue<Customer> windows[], int nWin); // Ϊ�µ��˿�ȷ����Ѷ���
_DSA_END
#endif // !__QUEUE_FUNCTION_H__
