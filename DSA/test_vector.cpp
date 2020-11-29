#include "vector.h"
#include <iostream>

template<typename T>
struct Increase { // 函数对象：递增一个T类对象
	virtual void operator()(T& e) { e++; } // 假设T可直接递增或已重载
};

template<typename T>
void increase(dsa::Vector<T>& V) { // 统一递增向量中的各元素
	Increase<T> VST; // 建立Increase<T>对象实例VST
	V.traverse(VST); // 以VST为基本操作进行遍历
}

template<typename T>
struct Print { // 函数对象：输出一个T类对象
	virtual void operator()(T& e) { std::cout << e << " "; } // 假设T已经重载<<
};

template<typename T>
void print(dsa::Vector<T>& V) { // 统一输出向量中的各元素
	Print<T> VST; // 建立Print<T>对象实例VST
	V.traverse(VST); // 以VST为基本操作进行遍历
}

template<typename T>
void visit(T& e) {
	std::cout << e << " ";
}

int main() {
	dsa::Vector<int> v;
	
	v.insert(0, 9);
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(0, 4);
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(1, 5);
	v.traverse(visit);
	std::cout << std::endl;

	v[1] = 2;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v[2] << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(3, 6);
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(1, 7);
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.remove(2) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(1, 3);
	v.traverse(visit);
	std::cout << std::endl;

	v.insert(3, 4);
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.size() << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.disordered() << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.find(9) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;
	
	std::cout << v.find(5) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	v.sort();
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.disordered() << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(1) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(4) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(8) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(9) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(10) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	v.uniquify();
	v.traverse(visit);
	std::cout << std::endl;

	std::cout << v.search(9) << std::endl;
	v.traverse(visit);
	std::cout << std::endl;

	increase(v);
	print(v);
	std::cout << std::endl;

	return 0;
}