// test_graphMatrix.cpp
#include "graphMatrix.h"
#include "visit.h"
#include <iostream>
using namespace dsa;
using namespace std;

int main() {	
	/*
#pragma region Test Vertex && Edge No Problem!
	GraphMatrix<int, int> gm;
	cout << "Create Graph: " << endl;
	cout << gm.insert(0) << endl;
	cout << gm.insert(1) << endl;
	cout << gm.insert(2) << endl;
	cout << gm.insert(3) << endl;
	cout << gm.insert(4) << endl;
	cout << "n: " << gm.n() << endl;
	cout << "e: " << gm.e() << endl;
	gm.insert(5, 1, 0, 1);
	gm.insert(6, 1, 0, 2);
	gm.insert(7, 1, 0, 3);
	gm.insert(8, 1, 0, 4);
	gm.insert(9, 1, 4, 0);
	gm.insert(10, 1, 3, 2);
	gm.insert(11, 1, 1, 2);
	cout << "e: " << gm.e() << endl;
	cout << endl;

	cout << "BFS:" << endl;
	gm.bfs(0);
	for (int i = 0; i < gm.n(); i++) {
		cout << gm.parent(i) << " ";
	}
	cout << endl;
	cout << gm.type(0, 1) << endl;
	cout << gm.type(1, 2) << endl;
	cout << gm.dTime(0) << endl;
	cout << gm.dTime(1) << endl;
	cout << endl;

	cout << "DFS:" << endl;
	gm.dfs(0);
	for (int i = 0; i < gm.n(); i++) {
		cout << gm.parent(i) << " ";
	}
	cout << endl;
	cout << gm.type(3, 2) << endl;
	cout << gm.type(4, 0) << endl;
	cout << gm.type(1, 2) << endl;
	cout << gm.type(0, 2) << endl;
	cout << endl;

	cout << "For vertex(0): " << endl;
	cout << gm.vertex(0) << endl;
	gm.vertex(0) = 99;
	cout << gm.vertex(0) << endl;
	cout << "inDeg(0): " << gm.inDegree(0) << endl;
	cout << "outDeg(0): " << gm.outDegree(0) << endl;
	int nbr = gm.firstNbr(0);
	cout << "firstNbr(0): " << nbr << endl;
	nbr = gm.nextNbr(0, nbr);
	cout << "nextNbr(0): " << nbr << endl;
	nbr = gm.nextNbr(0, nbr);
	cout << "nextNbr(0): " << nbr << endl;
	nbr = gm.nextNbr(0, nbr);
	cout << "nextNbr(0): " << nbr << endl;
	nbr = gm.nextNbr(0, nbr);
	cout << "nextNbr(0): " << nbr << endl;
	cout << "status(0): " << gm.status(0) << endl;
	cout << "dTime(0): " << gm.dTime(0) << endl;
	cout << "fTime(0): " << gm.fTime(0) << endl;
	cout << "parent(0): " << gm.parent(0) << endl;
	cout << "priority(0): " << gm.priority(0) << endl;
	cout << endl;
	cout << "For vertex(2): " << endl;
	cout << "inDeg(2): " << gm.inDegree(2) << endl;
	cout << "outDeg(2): " << gm.outDegree(2) << endl;
	cout << endl;

	cout << "Remove Vertex: " << endl;
	cout << gm.remove(0) << endl;
	cout << "n: " << gm.n() << endl;
	cout << "e: " << gm.e() << endl;
	cout << endl;

	cout << "For vertex(1) = 2 && edge(0, 1): " << endl;
	cout << gm.vertex(1) << endl;
	cout << gm.exists(0, 1) << endl;
	cout << gm.exists(1, 0) << endl;
	cout << gm.type(0, 1) << endl;
	cout << gm.edge(0, 1) << endl;
	cout << gm.weight(0, 1) << endl;
	gm.weight(0, 1) = 2;
	cout << gm.weight(0, 1) << endl;
	cout << gm.remove(0, 1) << endl;
	cout << "n: " << gm.n() << endl;
	cout << "e: " << gm.e() << endl;
	gm.remove(1);
	cout << "n: " << gm.n() << endl;
	cout << "e: " << gm.e() << endl;
	while (gm.n()) {
		gm.remove(0);
	}
	cout << "n: " << gm.n() << endl;
	cout << "e: " << gm.e() << endl;
#pragma endregion

#pragma region tSort
	GraphMatrix<char, int> gm2;
	gm2.insert('A');
	gm2.insert('B');
	gm2.insert('C');
	gm2.insert('D');
	gm2.insert('E');
	gm2.insert('F');
	gm2.insert(1, 1, 0, 2);
	gm2.insert(1, 1, 1, 2);
	gm2.insert(1, 1, 0, 3);
	gm2.insert(1, 1, 2, 3);
	gm2.insert(1, 1, 2, 4);
	gm2.insert(1, 1, 2, 5);
	gm2.insert(1, 1, 4, 5);
	auto s = gm2.tSort(0);
	Print<char> print;
	s->traverse(print);
	delete s;
#pragma endregion

#pragma region BCC
	gm2.bcc(0);
#pragma endregion

*/

#pragma region Prime
	GraphMatrix<int, int> gm3;
	gm3.insert(0);
	gm3.insert(1);
	gm3.insert(2);
	gm3.insert(3);
	gm3.insert(4);
	gm3.insert(5);
	gm3.insert(6);
	gm3.insert(1, 3, 0, 1);
	gm3.insert(1, 1, 1, 2);
	gm3.insert(1, 4, 0, 3);
	gm3.insert(1, 1, 3, 2);
	gm3.insert(1, 3, 2, 4);
	gm3.insert(1, 2, 2, 5);
	gm3.insert(1, 6, 3, 5);
	gm3.insert(1, 4, 3, 6);
	gm3.insert(1, 1, 5, 4);
	gm3.prim(0);
	cout << endl;
	cout << gm3.parent(3) << endl; // 0
	cout << gm3.parent(4) << endl; // 5
#pragma endregion

#pragma region Dijkstra
	gm3.dijkstra(0);
	cout << endl;
	cout << gm3.parent(3) << endl; // 0
	cout << gm3.parent(4) << endl; // 2
#pragma endregion

	return 0;
}