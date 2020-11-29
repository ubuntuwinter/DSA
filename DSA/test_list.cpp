#include "list.h"
#include <iostream>

template<typename T>
struct Increase { // �������󣺵���һ��T�����
	virtual void operator()(T& e) { e++; } // ����T��ֱ�ӵ�����������
};

template<typename T>
void increase(dsa::List<T>& L) { // ͳһ���������еĸ�Ԫ��
	Increase<T> VST; // ����Increase<T>����ʵ��VST
	L.traverse(VST); // ��VSTΪ�����������б���
}

template<typename T>
struct Print { // �����������һ��T�����
	virtual void operator()(T& e) { std::cout << e << " "; } // ����T�Ѿ�����<<
};

template<typename T>
void print(dsa::List<T>& L) { // ͳһ��������еĸ�Ԫ��
	Print<T> VST; // ����Print<T>����ʵ��VST
	L.traverse(VST); // ��VSTΪ�����������б���
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