#include "stack.h"
#include "stack_function.h"
#include <iostream>
using namespace std;

template<typename T>
struct Print { // �����������һ��T�����
	virtual void operator()(T& e) { std::cout << e << " "; } // ����T�Ѿ�����<<
};

template<typename T>
void print(dsa::Vector<T>& V) { // ͳһ��������еĸ�Ԫ��
	Print<T> VST; // ����Print<T>����ʵ��VST
	V.traverse(VST); // ��VSTΪ�����������б���
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