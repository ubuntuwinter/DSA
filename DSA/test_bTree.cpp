// test_bTree.cpp
#include "bTree.h"
#include "visit.h"
#include <iostream>
using namespace std;
using namespace dsa;

template<typename T>
void pprint(BTNodePosi(T) v) {
	Print<T> print;
	v->key.traverse(print);
	cout << endl;
	for (int i = 0; i < v->child.size(); i++) {
		if (v->child[i]) {
			pprint(v->child[i]);
		}
	}
}

int main() {
	BTree<int> btree;
	btree.insert(53);
	btree.insert(75);
	btree.insert(139);
	btree.insert(49);
	btree.insert(145);
	btree.insert(36);
	btree.insert(101);
	pprint(btree.root());
	cout << endl;
	btree.remove(101);
	btree.remove(53);
	btree.remove(75);
	btree.remove(139);
	btree.remove(49);
	btree.remove(145);
	btree.remove(36);
	pprint(btree.root());
	cout << endl;
	cout << btree.size() << endl;
	cout << endl;
	if (btree.search(33)) {
		cout << 1 << endl;
	}
	else {
		cout << 0 << endl;
	}
	return 0;
}