#include "vector.h"
#include <iostream>

template<typename T>
struct Increase { // �������󣺵���һ��T�����
	virtual void operator()(T& e) { e++; } // ����T��ֱ�ӵ�����������
};

template<typename T>
void increase(dsa::Vector<T>& V) { // ͳһ���������еĸ�Ԫ��
	Increase<T> VST; // ����Increase<T>����ʵ��VST
	V.traverse(VST); // ��VSTΪ�����������б���
}

template<typename T>
struct Print { // �����������һ��T�����
	virtual void operator()(T& e) { std::cout << e << " "; } // ����T�Ѿ�����<<
};

template<typename T>
void print(dsa::Vector<T>& V) { // ͳһ��������еĸ�Ԫ��
	Print<T> VST; // ����Print<T>����ʵ��VST
	V.traverse(VST); // ��VSTΪ�����������б���
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