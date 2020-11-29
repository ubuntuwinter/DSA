// pq.h
#pragma once
#ifndef __PQ_H__
#define __PQ_H__
#include "dsa.h"
_DSA_BEGIN
template<typename T>
struct PQ { // 优先队列PQ模板类
	virtual void insert(T) = 0; // 按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0; // 取出优先级最高的词条
	virtual T delMax() = 0; // 删除优先级最高的词条
};
_DSA_END
#endif // !__PQ_H__E
