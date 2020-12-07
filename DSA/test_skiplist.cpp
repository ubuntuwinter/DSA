// test_skiplist.cpp
#include "skiplist.h"
#include "visit.h"
#include <ctime>
using namespace std;
using namespace dsa;

int main() {
	srand(time(nullptr));

	Print<Entry<int, int>> print;
	Skiplist<int, int> sl;
	sl.put(1, 1);
	sl.put(2, 2);
	sl.put(3, 3);
	sl.put(4, 7);
	sl.put(5, 124);
	sl.put(7, 3);
	sl.put(6, 3);
	cout << *sl.get(1) << endl;
	cout << *sl.get(2) << endl;
	cout << *sl.get(3) << endl;
	auto p = sl.first();
	while (p && p != sl.last()->succ) {
		p->data->traverse(print);
		cout << endl;
		p = p->succ;
	}
	// cout << sl.remove(1) << endl;
	// cout << sl.remove(1) << endl;
	p = sl.first();
	while (p && p != sl.last()->succ) {
		p->data->traverse(print);
		cout << endl;
		p = p->succ;
	}
	return 0;
}