// queue_function.cpp
#include "queue.h"
#include "queue_function.h"
_DSA_BEGIN
void simulate(int nWin, int servTime) { // ��ָ����������������ʱ��ģ������ҵ��
	Queue<Customer>* windows = new Queue<Customer>[nWin]; // Ϊÿһ���ڴ���һ������
	for (int now = 0; now < servTime; now++) { // ���°�֮ǰ��ÿ��һ����λʱ��
		if (rand() % (1 + nWin)) { // �¹˿���nWin/(nWin + 1)�ĸ��ʵ���
			Customer c; c.time = 1 + rand() % 98; // �¹˿͵������ʱ�����ȷ��
			c.window = bestWindow(windows, nWin); // �¹˿ͼ����Ӧ����
		}
		for (int i = 0; i < nWin; i++) // �ֱ���
			if (!windows[i].empty()) // ���ǿն���
				if (--windows[i].front().time <= 0) // ���׹˿͵ķ���ʱ������һ����λ
					windows[i].dequeue(); // ������ϵĹ˿ͳ��У��ɺ�̹˿ͽ���
	} // for
	delete[] windows; // �ͷ����ж��У���ǰ��~List()���Զ���ն��У�
}

int bestWindow(Queue<Customer> windows[], int nWin) { // Ϊ�µ��˿�ȷ����Ѷ���
	int minSize = windows[0].size(), optWin = 0; // ���Ŷ��У����ڣ�
	for (int i = 1; i < nWin; i++) // �����д�����
	{
		if (minSize > windows[i].size()) // ��ѡ��
		{
			minSize = windows[i].size(); optWin = i;
		} // ���������
	}
	return optWin; // ����
}
_DSA_END