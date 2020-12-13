// hashtable.h
#pragma once
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include "dsa.h"
#include "dictionary.h"
#include "bitmap.h"
_DSA_BEGIN
template<typename K, typename V> // key��value
class Hashtable : public Dictionary<K, V> { // ����Dictionary�ӿڵ�Hashtableģ����
private:
	Entry<K, V>** ht; // Ͱ���飬��Ŵ���ָ��
	int M; // Ͱ��������
	int N; // ��������
	Bitmap* lazyRemoval; // ����ɾ�����
#define lazilyRemoved(x) (lazyRemoval->test(x));
#define markAsRemoved(x) (lazyRemoval->set(x));
protected:
	int probe4Hit(const K& k); // �عؼ���k��Ӧ�Ĳ��������ҵ�����ƥ���Ͱ
	int probe4Free(const K& k); // �عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ
	void rehash(); // ��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
public:
	Hashtable(int c = 5); // ����һ��������С��c��ɢ�б�
	~Hashtable(); // �ͷ�Ͱ���鼰���и����ǿգ�Ԫ����ָ��Ĵ���
	int size() const override { return N; } // ��ǰ�Ĵ�����Ŀ
	bool put(K, V) override; // ���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
	V* get(K k) override; // ��ȡ 
	bool remove(K k) override; // ɾ��
};

int primeNLT(int c, int n, const char* file) { // ����file�ļ��еļ�¼����[c, n)��ȡ��С������
	Bitmap B(file, n); // file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	while (c < n) { // ��c��ʼ����λ��
		if (B.test(c)) c++; // ���Լ���
		else return c; // �����׸����ֵ�����
	}
	return c; // ��û������������������n��ʵ���в�����˼򻯴���
}

template<typename K, typename V>
Hashtable<K, V>::Hashtable(int c) { // ����ɢ�б�����Ϊ
	M = primeNLT(c, 1048576, "prime-1048576-bitmap.txt"); // ��С��c������M
	N = 0; ht = new Entry<K, V>*[M]; // ����Ͱ���飨����˶�����ɹ�������ʼװ������ΪN/M = 0%
	memset(ht, 0, sizeof(Entry<K, V*>) * M);
	lazyRemoval = new Bitmap(M);
}

template<typename K, typename V> 
Hashtable<K, V>::~Hashtable() { // ����ǰ�ͷ�Ͱ���鼰�ǿմ���
	for (int i = 0; i < M; i++) // ��һ����Ͱ
		if (ht[i]) delete ht[i]; // �ͷŷǿյ�Ͱ
	delete[] ht; // �ͷ�Ͱ����
	delete lazyRemoval; // �ͷ�����ɾ�����
}



_DSA_END
#endif // !__HASHTABLE_H__
