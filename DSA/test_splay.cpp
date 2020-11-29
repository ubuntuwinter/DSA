// test_splay.cpp
#include "splay.h"
#include "visit.h"
using namespace std;
using namespace dsa;

int main() {
	Splay<int> splay;
	splay.insert(1);
	splay.insert(2);
	splay.insert(3);
	splay.insert(4);
	splay.insert(5);
	splay.insert(6);
	splay.insert(7);
	Print<int> print;
	splay.travLevel(print);
	cout << endl;
	splay.travIn(print);
	cout << endl;
	splay.search(1);
	splay.travLevel(print);
	cout << endl;
	splay.travIn(print);
	cout << endl;
	splay.remove(1);
	splay.travLevel(print);
	cout << endl;
	splay.travIn(print);
	cout << endl;
	splay.remove(4);
	splay.travLevel(print);
	cout << endl;
	splay.travIn(print);
	cout << endl;
	splay.remove(2);
	splay.remove(3);
	splay.remove(5);
	splay.remove(6);
	splay.remove(7);
	splay.travLevel(print);
	cout << endl;
	splay.travIn(print);
	cout << endl;
	return 0;
}