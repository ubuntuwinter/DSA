// test_splay.cpp
#include "splay.h"
#include "visit.h"
using namespace std;
using namespace dsa;

int main() {
	Splay<int> splay;
	splay.insert(0);
	splay.insert(1);
	splay.insert(2);
	splay.insert(3);
	splay.insert(4);
	return 0;
}