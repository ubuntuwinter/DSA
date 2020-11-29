// queen.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
struct Queen { // �ʺ���
	int x, y; // �ʺ��������ϵ�λ������
	Queen(int xx = 0, int yy = 0) :x(xx), y(yy) {}
	bool operator==(Queen const& q) const { // �����еȲ��������Լ�ⲻͬ�ʺ�֮����ܵĳ�ͻ
		return (x == q.x) // �г�ͻ����һ�����ʵ���ᷢ������ʡ�ԣ�
			|| (y == q.y) // �г�ͻ
			|| (x + y == q.x + q.y) // �����Խ��߳�ͻ
			|| (x - y == q.x - q.y); // �ط��Խ��߳�ͻ
	}
	bool operator!=(Queen const& q) const { return !(*this == q); } // ���ز��Ȳ�����
};
void placeQueens(int N) { // N�ʺ����⣨�����棩��������̽/���ݵĲ��ԣ�����ջ��¼���ҵĽ��
	Stack<Queen> solu; // ��ţ����֣����ջ
	Queen q(0, 0); // ��ԭ�����
	int nCheck = 0, nSolu = 0;
	do {
		if (N <= solu.size() || N <= q.y) { // ���ѳ��磬��
			q = solu.pop(); q.y++; // ����һ�У�������̽��һ��
		}
		else {
			while ((q.y < N) && (0 <= solu.find(q))) { // ͨ�������лʺ�ıȶ�
					q.y++; nCheck++; // �����ҵ��ɰڷ���һ�ʺ����
			}
			if (q.y < N) { // �����ڿɰڷŵ��У���
				solu.push(q); // ���ϵ�ǰ�ʺ�
				if (N <= solu.size()) nSolu++; // �����ֽ��ѳ�Ϊȫ�ֽ⣬��ͨ������nSolu����
				q.x++; q.y = 0; // ת����һ�У��ӵ�0�п�ʼ����̽��һ�ʺ�
			}
		}
	} while ((0 < q.x) || (q.y < N)); // ���з�֧���ѻ���ٻ��֦֮���㷨����
}
_DSA_END