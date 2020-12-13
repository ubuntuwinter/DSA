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
	bool put(K k, V v) override; // ���루��ֹ��ͬ�������ʿ���ʧ�ܣ�
	V* get(K k) override; // ��ȡ 
	bool remove(K k) override; // ɾ��
};

static size_t hashCode(char c) { return (size_t)c; } // �ַ�
static size_t hashCode(int k) { return (size_t)k; } // �����Լ���������
static size_t hashCode(long long i) { return (size_t)((i >> 32) + (int)i); }
static size_t hashCode(char s[]) { // �����ַ�����ѭ����λɢ���루cyclic shift hash code��
	int h = 0; // ɢ����
	for (size_t n = strlen(s), i = 0; i < n; i++) { // �������ң���һ����ÿһ�ַ�
		h = (h << 5) | (h >> 27); h += (int)s[i]; // ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
	}
	return (size_t)h; // ������õ�ɢ���룬ʵ���Ͽ����λ���Ƶġ�����ʽɢ���롱
}

int primeNLT(int c, int n, const char* file) { // ����file�ļ��еļ�¼����[c, n)��ȡ��С������
	Bitmap B(file, n); // file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	while (c < n) { // ��c��ʼ����λ��
		if (B.test(c)) c++; // ���Լ���
		else return c; // �����׸����ֵ�����
	}
	return c; // ��û������������������n��ʵ���в�����˼򻯴���
}

/**
* �عؼ���k��Ӧ�Ĳ��������ҵ���֮ƥ���Ͱ�������Һ�ɾ������ʱ���ã�
* ��̽���Զ��ֶ����������ѡȡ���������������̽����Ϊ��
*/
template<typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M; // ����ʼͰ�������෨ȷ��������
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r))) {
		r = (r + 1) % M; // �ز�������̽���������г�ͻ��Ͱ���Լ���������ɾ����ǵ�Ͱ
	}
	return r; // �����߸���ht[r]�Ƿ�Ϊ�գ������жϲ����Ƿ�ɹ�
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

template<typename K, typename V>
bool Hashtable<K, V>::put(K k, V v) { // ɢ�б��������
	if (ht[probe4Hit(k)]) return false; // ��ͬԪ�ز����ظ�����
	int r = probe4Free(k); // Ϊ�´����Ҹ���Ͱ��ֻҪװ����˿��Ƶõ�����Ȼ�ɹ���
	ht[r] = new Entry<K, V>(k, v); ++N; // ���루ע�⣺����ɾ��������踴λ��
	if (N * 2 > M) rehash(); // װ�����Ӹ���50%����ɢ��
	return true; 
}

template<typename K, typename V>
V* Hashtable<K, V>::get(K k) { // ɢ�б���������㷨
	int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : NULL; // ��ֹ������keyֵ��ͬ
}

_DSA_END
#endif // !__HASHTABLE_H__
