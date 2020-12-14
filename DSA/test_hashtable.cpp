// test_hashtable.cpp
#include "hashtable.h"
#include <iostream>
using namespace std;
using namespace dsa;

int main() {
	Hashtable<int, int> ht(100);
	ht.put(1, 10);
	cout << *ht.get(1) << endl;
	cout << ht.size() << endl;
	ht.remove(1);
	cout << ht.size() << endl;
	return 0;
}