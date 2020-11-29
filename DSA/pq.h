// pq.h
#pragma once
#ifndef __PQ_H__
#define __PQ_H__
#include "dsa.h"
_DSA_BEGIN
template<typename T>
struct PQ { // ���ȶ���PQģ����
	virtual void insert(T) = 0; // ���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0; // ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; // ɾ�����ȼ���ߵĴ���
};
_DSA_END
#endif // !__PQ_H__E
