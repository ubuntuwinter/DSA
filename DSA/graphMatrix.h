// graghMatrix.h
#pragma once
#ifndef __GRAPHMATRIX_H__
#define __GRAPHMATRIX_H__
#include "dsa.h"
#include "vector.h"
#include "graph.h"
_DSA_BEGIN
template<typename Tv>
struct Vertex { // �������
	Tv data; int inDegree, outDegree; VStatus status; // ���ݡ����������״̬
	int dTime, fTime; // ʱ���ǩ
	int parent; int priority; // �ڱ������еĸ��ڵ㡢���ȼ���
	Vertex(Tv const& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {} // �ݲ�����Ȩ�����
};

template<typename Te>
struct Edge { // �߶���
	Te data; int weight; EType type; // ���ݡ�Ȩ�ء�����
	Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {} // ����
};

template<typename Tv, typename Te> // �������͡�������
class GraphMatrix :public Graph<Tv, Te> { // �������������ڽӾ�����ʽʵ�ֵ�ͼ
private:
	Vector<Vertex<Tv>> V; // ���㼯��������
	Vector<Vector<Edge<Te>*>> E; // �߼����ڽӾ���
public:
	GraphMatrix() { Graph<Tv, Te>::_n = Graph<Tv, Te>::_e = 0; } // ����
	~GraphMatrix() { // ����
		for (int j = 0; j < Graph<Tv, Te>::_n; j++) { // ���ж�̬������
			for (int k = 0; k < Graph<Tv, Te>::_n; k++) { // �߼�¼
				delete E[j][k]; // �������
			}
		}
	}
	// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
	virtual Tv& vertex(int i) override { return V[i].data; } // ����
	virtual int inDegree(int i) override { return V[i].inDegree; } // ���
	virtual int outDegree(int i) override { return V[i].outDegree; } // ����
	virtual int firstNbr(int i) override { return nextNbr(i, Graph<Tv, Te>::_n); } // �׸��ڽӶ���
	virtual int nextNbr(int i, int j) override { // ����ڶ���j����һ�ڽӶ���
		while ((-1 < j) && (!exists(i, --j))); return j; // ����������̽
	}
	virtual VStatus& status(int i) override { return V[i].status; } // ״̬
	virtual int& dTime(int i) override { return V[i].dTime; } // ʱ���ǩdTime
	virtual int& fTime(int i) override { return V[i].fTime; } // ʱ���ǩfTime
	virtual int& parent(int i) override { return V[i].parent; } // �ڱ������еĸ���
	virtual int& priority(int i) override { return V[i].priority; } // �ڱ������е����ȼ���
	// ����Ķ�̬����
	virtual int insert(Tv const& vertex) override { // ���붥�㣬���ر��
		for (int j = 0; j < Graph<Tv, Te>::_n; j++) {
			E[j].insert(NULL); // ������Ԥ��һ��Ǳ�ڵĹ�����
		}
		Graph<Tv, Te>::_n++;
		E.insert(Vector<Edge<Te>*>(Graph<Tv, Te>::_n, Graph<Tv, Te>::_n, (Edge<Te>*)NULL)); // �����¶����Ӧ�ı�����
		return V.insert(Vertex<Tv>(vertex)); // ������������һ������
	}
	virtual Tv remove(int i) override { // ɾ����i�����㼰������ߣ�0 <= i < n��
		for (int j = 0; j < Graph<Tv, Te>::_n; j++) { // ���г���
			if (exists(i, j)) { delete E[i][j]; Graph<Tv, Te>::_e--; V[j].inDegree--; } // ����ɾ��
		}
		E.remove(i); Graph<Tv, Te>::_n--; // ɾ����i��
		Tv vBak = vertex(i); V.remove(i); // ɾ������i
		for (int j = 0; j < Graph<Tv, Te>::_n; j++) { // �������
			if (Edge<Te>* e = E[j].remove(i)) { delete e; Graph<Tv, Te>::_e--; V[j].outDegree--; } // ����ɾ��
		}
		return vBak; // ���ر�ɾ���������Ϣ
	}
	// �ߵ�ȷ�ϲ���
	virtual bool exists(int i, int j) override { // ��(i, j)�Ƿ����
		return (0 <= i) && (i < Graph<Tv, Te>::_n) && (0 <= j) && (j < Graph<Tv, Te>::_n) && E[i][j] != NULL;
	}
	// �ߵĻ�����������ѯ����i��j֮������ߣ�0 <= i, j < n��exists(i, j)
	virtual EType& type(int i, int j) override { return E[i][j]->type; } // ��(i, j)������
	virtual Te& edge(int i, int j) override { return E[i][j]->data; } // ��(i, j)������
	virtual int& weight(int i, int j) { return E[i][j]->weight; } // ��(i, j)��Ȩ��
	// �ߵĶ�̬����
	virtual void insert(Te const& edge, int w, int i, int j) override { // ����Ȩ��Ϊw�ı�e = (i, j)
		if (exists(i, j)) return; // ȷ���ñ��в�����
		E[i][j] = new Edge<Te>(edge, w); // �����±�
		Graph<Tv, Te>::_e++; V[i].outDegree++; V[j].inDegree++; // ���±߼������������Ķ���
	}
	virtual Te remove(int i, int j) { // ɾ������i��j֮������ߣ�exists(i, j)��
		Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; // ���ݺ�ɾ���߼�¼
		Graph<Tv, Te>::_e--; V[i].outDegree--; V[j].inDegree--; // ���±߼������������Ķ���
		return eBak; // ���ر�ɾ���ߵ���Ϣ
	}
};
_DSA_END
#endif // !__GRAPHMATRIX_H__
