// test_redblack.cpp
#include "redblack.h"
#include "visit.h"
using namespace std;
using namespace dsa;

int main() {
	RedBlack<int> rb;
	rb.insert(70);
	rb.insert(80); 
	rb.insert(90);
	rb.insert(10);
	rb.insert(100);
	rb.insert(60);
	rb.insert(120);
	rb.insert(130);
	rb.insert(140);
	rb.insert(150);
	cout << "size: " << rb.size() << endl;
	Print<int> print;
	rb.travLevel(print);
	cout << endl;
	rb.travIn(print);
	cout << endl;
	rb.remove(100);
	rb.remove(70);
	rb.remove(150);
	rb.remove(10);
	rb.remove(60);
	cout << "size: " << rb.size() << endl;
	rb.travLevel(print);
	cout << endl;
	rb.travIn(print);
	cout << endl;
	return 0;
}