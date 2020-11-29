#pragma once
#ifndef __VISIT_H__
#define __VISIT_H__
#include "dsa.h"
#include <iostream>
_DSA_BEGIN
template<typename T>
struct Print { // 函数对象：输出一个T类对象
	virtual void operator()(T& e) { std::cout << e << " "; } // 假设T已经重载<<
};
_DSA_END
#endif // !__VISIT_H__
