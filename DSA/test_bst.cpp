// test_bst.cpp
#include <iostream>
#include "bst.h"
#include "visit.h"
using namespace std;
using namespace dsa;

int main() {
	BST<int> bst;
	bst.insert(3);
	bst.insert(1);
	bst.insert(2);
	bst.insert(5);
	bst.insert(4);
	Print<int> print;
	bst.travIn(print);
	cout << endl;
	bst.travLevel(print);
	cout << endl;
	bst.remove(3);
	bst.travIn(print);
	cout << endl;
	bst.travLevel(print);
	cout << endl;
	BinNodePosi(int) root = bst.search(4);
	if (root == bst.root()) {
		cout << "Yes!" << endl;
	}
	else {
		cout << "No!" << endl;
	}
	return 0;
}