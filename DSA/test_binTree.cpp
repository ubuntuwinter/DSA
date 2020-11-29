// test_binTree.cpp
#include <iostream>
#include "binTree.h"
#include "visit.h"
using namespace std;

int main() {
	dsa::BinTree<int> bt;
	dsa::BinNodePosi(int) root = bt.insertAsRoot(1); // 根
	cout << bt.size() << endl; // 1
	dsa::BinNodePosi(int) left = bt.insertAsLC(root, 2); // 左
	cout << bt.size() << endl; // 2
	dsa::BinNodePosi(int) right = bt.insertAsRC(root, 3); // 右
	cout << bt.size() << endl; // 3
	dsa::BinTree<int>* subt1 = bt.secede(left); // 摘下左子树
	cout << bt.size() << endl; // 3 - 1 = 2
	dsa::BinTree<int>* subt2 = new dsa::BinTree<int>();
	subt2->insertAsRoot(4);
	subt2->insertAsLC(subt2->root(), 5);
	bt.attachAsRC(right, subt2); // 挂到右子树上
	cout << bt.size() << endl; // 2 + 2 = 4
	subt1->insertAsLC(subt1->root(), 6);
	bt.attachAsLC(root, subt1); // 挂回左子树
	cout << bt.size() << endl; // 4 + 2 = 6
	cout << bt.empty() << endl; // 0
	cout << bt.root()->height << endl; // 3
	dsa::Print<int> print;
	bt.travLevel(print);
	cout << endl;
	cout << bt.root()->succ()->data << endl; // 3
	/*
						1
					   / \
					  2   3
					 /     \
					6       4
					       /
						  5
	*/
	return 0;
}