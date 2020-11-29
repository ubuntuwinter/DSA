#include "stack.h"
#include "stack_function.h"
#include <iostream>
using namespace std;

template<typename T>
struct Print { // 函数对象：输出一个T类对象
	virtual void operator()(T& e) { std::cout << e << " "; } // 假设T已经重载<<
};

template<typename T>
void print(dsa::Vector<T>& V) { // 统一输出向量中的各元素
	Print<T> VST; // 建立Print<T>对象实例VST
	V.traverse(VST); // 以VST为基本操作进行遍历
}

int main() {
	dsa::Stack<char> stack;
	char* RPN = new char[1]();
	cout << dsa::evaluate("(0!+1)*2^(3!+4)-(5!-67-(8+9))",RPN) << endl;
	cout << RPN << endl;
	dsa::convert(stack, 37, 2);
	while (!stack.empty()) {
		cout << stack.pop();
	}
	cout << endl;
	delete[] RPN;
	return 0;
}