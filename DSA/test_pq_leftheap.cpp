// test_pq_leftheap.cpp
#include "pq_leftheap.h"
#include "visit.h"
#include <iostream>
using namespace dsa;
using namespace std;
using Heap = PQ_LeftHeap<int>;

int main() {
	Print<int> print;
	Heap heap;
	heap.insert(1);
	heap.insert(2);
	heap.insert(3);
	heap.insert(4);
	heap.insert(5);
	heap.travIn(print);
	cout << endl;
	heap.travPre(print);
	cout << endl;
	cout << heap.size() << endl;
	cout << heap.delMax() << endl;
	cout << heap.delMax() << endl;
	cout << heap.getMax() << endl;
	cout << heap.size() << endl;
	heap.travIn(print);
	cout << endl;
	heap.travPre(print);
	cout << endl;
	int a[] = { 1,3,5,7,8,4,6,6 };
	Heap heap2(a, 8);
	heap2.travIn(print);
	cout << endl;
	heap2.travPre(print);
	cout << endl;
	cout << heap2.size() << endl;
	return 0;
}