#pragma once
#ifndef __VISIT_H__
#define __VISIT_H__
#include "dsa.h"
#include <iostream>
_DSA_BEGIN
template<typename T>
struct Print { // �����������һ��T�����
	virtual void operator()(T& e) { std::cout << e << " "; } // ����T�Ѿ�����<<
};
_DSA_END
#endif // !__VISIT_H__
