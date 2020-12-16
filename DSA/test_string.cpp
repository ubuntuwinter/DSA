// test_string.cpp
#include "string.h"
#include <iostream>
using namespace std;
using namespace dsa;

int main() {
	char T[] = "Data Structure";
	char P[] = "Structure";

	cout << "Brute Force 1: " << match_BruteForce1(P, T) << endl;
	cout << "Brute Force 2: " << match_BruteForce2(P, T) << endl;
	cout << "KMP: " << match_KMP(P, T) << endl;
	cout << "BM: " << match_BM(P, T) << endl;
	return 0;
}