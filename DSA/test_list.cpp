#include "list.h"
#include <iostream>

template<typename T>
struct Increase { // 函数对象：递增一个T类对象
	virtual void operator()(T& e) { e++; } // 假设T可直接递增或已重载
};

template<typename T>
void increase(dsa::List<T>& L) { // 统一递增向量中的各元素
	Increase<T> VST; // 建立Increase<T>对象实例VST
	L.traverse(VST); // 以VST为基本操作进行遍历
}

template<typename T>
struct Print { // 函数对象：输出一个T类对象
	virtual void operator()(T& e) { std::cout << e << " "; } // 假设T已经重载<<
};

template<typename T>
void print(dsa::List<T>& L) { // 统一输出向量中的各元素
	Print<T> VST; // 建立Print<T>对象实例VST
	L.traverse(VST); // 以VST为基本操作进行遍历
}

template<typename T>
void visit(T& e) {
	std::cout << e << " ";
}

int main() {
	dsa::List<int> l;

	l.insertAsLast(9);
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(4);
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(5);
	l.traverse(visit);
	std::cout << std::endl;

	l[1] = 2;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l[2] << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(6);
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(6);
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(7);
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.remove(l.last()) << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(3);
	l.traverse(visit);
	std::cout << std::endl;

	l.insertAsLast(4);
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.size() << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.disordered() << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.find(9)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.find(5)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	l.sort();
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.disordered() << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(1)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(4)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(8)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(9)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(10)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	l.uniquify();
	l.traverse(visit);
	std::cout << std::endl;

	std::cout << l.search(9)->data << std::endl;
	l.traverse(visit);
	std::cout << std::endl;

	increase(l);
	print(l);
	std::cout << std::endl;

	l.reverse();
	print(l);
	std::cout << std::endl;

	return 0;
}