// test_avl.cpp
#include <iostream>
#include "avl.h"
#include "visit.h"
using namespace std;
using namespace dsa;

int main() {
	AVL<int> avl;
	for (int i = 0; i < 100; i++) {
		avl.insert(rand() % 100);
	}
	Print<int> print;
	avl.travIn(print);
	cout << endl;
	avl.travLevel(print);
	cout << endl;
	for (int i = 0; i < 100; i++) {
		avl.remove(rand() % 100);
	}
	avl.travIn(print);
	cout << endl;
	avl.travLevel(print);
	cout << endl;
	/*
	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);
	Print<int> print;
	avl.travIn(print);
	cout << endl;
	avl.travLevel(print);
	cout << endl;
	avl.remove(6);
	avl.remove(5);
	avl.travIn(print);
	cout << endl;
	avl.travLevel(print);
	cout << endl;
	*/
	return 0;
}