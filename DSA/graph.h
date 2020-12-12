// graph.h
#pragma once
#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "dsa.h"
#include "queue.h"
#include "stack.h"
#include <climits>
_DSA_BEGIN
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; // ����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; // ���ڱ�����������������

template<typename Tv, typename Te> // �������͡�������
class Graph { // ͼGraphģ����
private:
	void reset() { // ���ж��㡢�ߵĸ�����Ϣ��λ
		for (int i = 0; i < _n; i++) { // ���ж����
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1; // ״̬��ʱ���ǩ
			parent(i) = -1; priority(i) = INT_MAX; // ���ڱ������еģ����ڵ㣬���ȼ���
			for (int j = 0; j < _n; j++) { // ���бߵ�
				if (exists(i, j)) type(i, j) = UNDETERMINED; // ����
			}
		}
	}
	void BFS(int, int&); // ����ͨ�򣩹�����������㷨
	void DFS(int, int&); // ����ͨ��������������㷨
	void BCC(int, int&, Stack<int>&); // ����ͨ�򣩻���DFS��˫��ͨ�����ֽ��㷨
	bool TSort(int, int&, Stack<Tv>*); // ����ͨ�򣩻���DFS�����������㷨
	template<typename PU> void PFS(int, PU); // ����ͨ�����ȼ��������
protected:
	int _n; // ��������
	int _e; // ������
public:
	// ����
	int n() const { return _n; } // ��������
	virtual int insert(Tv const&) = 0; // ���붥�㣬���ر��
	virtual Tv remove(int) = 0; // ɾ�����㼰������ߣ����ظö�����Ϣ
	virtual Tv& vertex(int) = 0; // ����v�����ݣ��ö����ȷ���ڣ�
	virtual int inDegree(int) = 0; // ����v����ȣ��ö����ȷ���ڣ�
	virtual int outDegree(int) = 0; // ����v�ĳ��ȣ��ö����ȷ���ڣ�
	virtual int firstNbr(int) = 0; // ����v���׸��ڽӶ���
	virtual int nextNbr(int, int) = 0; // ����v�ģ�����ڶ���j�ģ���һ�ڽӶ���
	virtual VStatus& status(int) = 0; // ����v��״̬
	virtual int& dTime(int) = 0; // ����v��ʱ���ǩdtime
	virtual int& fTime(int) = 0; // ����v��ʱ���ǩftime
	virtual int& parent(int) = 0; // ����v�ڱ������еĸ���
	virtual int& priority(int) = 0; // ����v�ڱ������е����ȼ���
	// �ߣ�����Լ��������߾�ͳһת��Ϊ�������һ������ߣ��Ӷ�������ͼ��������ͼ������
	int e() const { return _e; } // ������
	virtual bool exists(int, int) = 0; // ��(v, u)�Ƿ����
	virtual void insert(Te const&, int, int, int) = 0; // �ڶ���v��u֮�����Ȩ��Ϊw�ı�e
	virtual Te remove(int, int) = 0; // ɾ������v��u֮��ı�e�����ظñ���Ϣ
	virtual EType& type(int, int) = 0; // ��(v, u)������
	virtual Te& edge(int, int) = 0; // ��(v, u)�����ݣ��ñߵ�ȷ���ڣ�
	virtual int& weight(int, int) = 0; // ��(v, u)��Ȩ��
	// �㷨
	void bfs(int); // ������������㷨
	void dfs(int); // ������������㷨
	void bcc(int); // ����DFS��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int); // ����DFS�����������㷨
	void prim(int); // ��С֧����Prim�㷨
	void dijkstra(int); // ���·��Dijkstra�㷨
	template<typename PU> void pfs(int, PU); // ���ȼ��������
};

template<typename Tv, typename Te> // �����������BFS�㷨��������ͨ��
void Graph<Tv, Te>::BFS(int v, int& clock) { // assert: 0 <= v < n
	Queue<int> Q; // ���븨������
	status(v) = DISCOVERED; Q.enqueue(v); // ��ʼ�����
	while (!Q.empty()) { // ��Q���֮ǰ������
		int v = Q.dequeue(); dTime(v) = ++clock; // ȡ�����׶���v
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { // ö��v�������ھ�u
			if (UNDISCOVERED == status(u)) { // ��u��δ�����֣���
				status(u) = DISCOVERED; Q.enqueue(u); // ���ָö���
				type(v, u) = TREE; parent(u) = v; // ����������չ֧����
			}
			else { // ��u�ѱ����֣����������ѷ�����ϣ���
				type(v, u) = CROSS; // ��(v, u)����Ϊ���
			}
		}
		status(v) = VISITED; // ���ˣ���ǰ����������
	}
}

template<typename Tv, typename Te> // �����������DFS�㷨��������ͨ��
void Graph<Tv, Te>::DFS(int v, int& clock) { // assert: 0 <= v < n
	dTime(v) = ++clock; status(v) = DISCOVERED; // ���ֵ�ǰ����
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { // ö��v�������ھ�
		switch (status(u)) { // ������״̬�ֱ���
		case UNDISCOVERED: // u��δ���֣���ζ��֧���������ڴ���չ
			type(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
		case DISCOVERED: // u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
			type(v, u) = BACKWARD; break;
		default: // u�ѱ�������ϣ�VISITED������ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	}
	status(v) = VISITED; fTime(v) = ++clock; // ���ˣ���ǰ����v����������
}

#define hca(x) (fTime(x)) // ���ô˴����õ�fTime[]�䵱hac[]
template<typename Tv, typename Te> // �������͡�������
void Graph<Tv, Te>::BCC(int v, int& clock, Stack<int>& S) { // assert: 0 <= v < n
	hca(v) = dTime(v) = ++clock; status(v) = DISCOVERED; S.push(v); // v�����ֲ���ջ
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { // ö��v�������ھ�u
		switch (status(u)) { // ����u��״̬�ֱ���
		case UNDISCOVERED:
			parent(u) = v; type(v, u) = TREE; BCC(u, clock, S); // �Ӷ���u������
			if (hca(u) < dTime(v)) { // �������غ�������u��ͨ������ߣ���ָ��v��������
				hca(v) = min(hca(v), hca(u)); // ��v�����
			}
			else { // ������vΪ�ؽڵ㣨u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ�����
				while (v != S.pop()); // ���ε�����ǰBCC�еĽڵ㣬��ɸ���ʵ������ת���������ṹ
				S.push(v); // ���һ�����㣨�ؽڵ㣩������ջ������̯����һ��
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; // ���(v, u)�������ա�ԽСԽ�ߡ���׼��
			if (u != parent(v)) hca(v) = min(hca(v), dTime(u)); // ����hca[v]
			break;
		default: // VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED; // ��v�ķ��ʽ���
}
#undef hca

template<typename Tv, typename Te> // ����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) { // assert: 0 <= v < n
	dTime(v) == ++clock; status(v) = DISCOVERED; // ���ֶ���v
	for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { // ö��v�������ھ�u
		switch (status(u)) { // ����u��״̬�ֱ���
		case UNDISCOVERED:
			parent(u) = v; type(v, u) = TREE;
			if (!TSort(u, clock, S)) { // �Ӷ���u��������������
				return false; // ��u��������������������ȫͼ�����ˣ����ʷ��ز�����
			}
			break;
		case DISCOVERED:
			type(v, u) = BACKWARD; // һ�����ֺ���ߣ���DAG������
			return false; // �������룬�ʷ��ز�����
		default: // VISITED (digraphs only)
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
			break;
		}
	}
	status(v) = VISITED; S->push(vertex(v)); // ���㱻���ΪVISITEDʱ�������ջ
	return true; // v������������������
}

template<typename Tv, typename Te> // �����������BFS�㷨��ȫͼ��
void Graph<Tv, Te>::bfs(int s) { // assert: 0 <= s < n
	reset(); int clock = 0; int v = s; // ��ʼ��
	do { // ��һ������ж���
		if (UNDISCOVERED == status(v)) // һ��������δ���ֵĶ���
			BFS(v, clock); // ���Ӹö����������һ��BFS
	} while (s != (v = (++v % _n))); // ����ż�飬�ʲ�©����
}

template<typename Tv, typename Te> // �����������DFS�㷨��ȫͼ��
void Graph<Tv, Te>::dfs(int s) { // assert: 0 <= s < n
	reset(); int clock = 0; int v = s; // ��ʼ��
	do { // ��һ������ж���
		if (UNDISCOVERED == status(v)) // һ��������δ���ֵĶ���
			DFS(v, clock); // ���Ӹö����������һ��DFS
	} while (s != (v = (++v % _n))); // ����ż�飬�ʲ�©����
}

template<typename Tv, typename Te> // ����DFS��BCC�ֽ��㷨
void Graph<Tv, Te>::bcc(int s) {
	reset(); int clock = 0; int v = s; Stack<int> S; // ջS���Լ�¼�ѷ��ʵĶ���
	do {
		if (UNDISCOVERED == status(v)) { // һ������δ���ֵĶ��㣨����ͨ������
			BCC(v, clock, S); // ���Ӹö����������һ��BCC
			S.pop(); // �������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
		}
	} while (s != (v = (++v % _n)));
}

template<typename Tv, typename Te> // ����DFS�����������㷨
Stack<Tv>* Graph<Tv, Te>::tSort(int s) { // assert: 0 <= s < n
	reset(); int clock = 0; int v = s;
	Stack<Tv>* S = new Stack<Tv>; // ��ջ��¼���򶥵�
	do {
		if (UNDISCOVERED == status(v)) {
			if (!TSort(v, clock, S)) { // clock���Ǳ���
				while (!S->empty()) { // ��һ��ͨ���༴��ͼ����DAG
					S->pop(); break; // �򲻱ؼ������㣬��ֱ�ӷ���
				}
			}
		}
	} while (s != (v = (++v % _n)));
	return S; // ������ΪDAG����S�ڸ������Զ�������򣻷��򣨲������������򣩣�S��
}

template<typename Tv, typename Te> // �������͡�������
template<typename PU> // ���ȼ�������
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) { // ��ʼ�������s����PFS����
	priority(s) = 0; status(s) = VISITED; parent(s) = -1; // ��ʼ�������s����PFS����
	while (1) { // ����һ����ͱ߼���PFS����
		for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w)) {
			prioUpdater(this, s, w); // ���¶���w�����ȼ����丸����
		}
		for (int shortest = INT_MAX, w = 0; w < _n; w++) {
			if (UNDISCOVERED == status(w)) { // ����δ����������Ķ�����
				if (shortest > priority(w)) { // ѡ����һ��
					shortest = priority(w); s = w; // ���ȼ���ߵĶ���s
				}
			}
		}
		if (VISITED == status(s)) break; // ֱ�����ж�����Ѽ���
		status(s) = VISITED; type(parent(s), s) = TREE; // ��s�����丸�����߼��������
	}
} // ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
	reset(); int v = s; // ��ʼ��
	do {
		if (UNDISCOVERED == status(v)) {
			PFS(v, prioUpdater);
		}
	} while (s != (v = (++v % _n)));
}

template<typename Tv, typename Te>
struct PrimePU { // ���Prim�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v)) { // ����ukÿһ��δ���ֵ��ڽӶ���v
			if (g->priority(v) > g->weight(uk, v)) { // ��Prime�������ɳ�
				g->priority(v) = g->weight(uk, v); // �������ȼ�������
				g->parent(v) = uk; // ���¸��ڵ�
			}
		}
	}
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) {
	PrimePU<Tv, Te> primePU;
	pfs(s, primePU);
}

template<typename Tv, typename Te>
struct DijkstraPU { // ���Dijkstra�㷨�Ķ������ȼ�������
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v) {
		if (UNDISCOVERED == g->status(v)) { // ����ukÿһ��δ���ֵ��ڽӶ���v����Dijkstra����
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) { // ���ɳ�
				g->priority(v) = g->priority(uk) + g->weight(uk, v); // �������ȼ�������
				g->parent(v) = uk; // ��ͬʱ���¸��ڵ�
			}
		}
	}
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {
	DijkstraPU<Tv, Te> dijkstraPU;
	pfs(s, dijkstraPU);
}

_DSA_END
#endif // !__GRAPH_H__
