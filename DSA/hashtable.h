// hashtable.h
#pragma once
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include "dsa.h"
#include "dictionary.h"
#include "bitmap.h"
_DSA_BEGIN
template<typename K, typename V> // key、value
class Hashtable : public Dictionary<K, V> { // 符合Dictionary接口的Hashtable模板类
private:
	Entry<K, V>** ht; // 桶数组，存放词条指针
	int M; // 桶数组容量
	int N; // 词条数量
	Bitmap* lazyRemoval; // 懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x));
#define markAsRemoved(x) (lazyRemoval->set(x));
protected:
	int probe4Hit(const K& k); // 沿关键码k对应的查找链，找到词条匹配的桶
	int probe4Free(const K& k); // 沿关键码k对应的查找链，找到首个可用空桶
	void rehash(); // 重散列算法：扩充桶数组，保证装填因子在警戒线以下
public:
	Hashtable(int c = 5); // 创建一个容量不小于c的散列表
	~Hashtable(); // 释放桶数组及其中各（非空）元素所指向的词条
	int size() const override { return N; } // 当前的词条数目
	bool put(K, V) override; // 插入（禁止雷同词条，故可能失败）
	V* get(K k) override; // 读取 
	bool remove(K k) override; // 删除
};

int primeNLT(int c, int n, const char* file) { // 根据file文件中的记录，在[c, n)内取最小的素数
	Bitmap B(file, n); // file已经按位图格式，记录了n以内的所有素数，因此只要
	while (c < n) { // 从c开始，逐位地
		if (B.test(c)) c++; // 测试即可
		else return c; // 返回首个发现的素数
	}
	return c; // 若没有这样的素数，返回n（实用中不能如此简化处理）
}

template<typename K, typename V>
Hashtable<K, V>::Hashtable(int c) { // 创建散列表，容量为
	M = primeNLT(c, 1048576, "prime-1048576-bitmap.txt"); // 不小于c的素数M
	N = 0; ht = new Entry<K, V>*[M]; // 开辟桶数组（还需核对申请成功），初始装填因子为N/M = 0%
	memset(ht, 0, sizeof(Entry<K, V*>) * M);
	lazyRemoval = new Bitmap(M);
}

template<typename K, typename V> 
Hashtable<K, V>::~Hashtable() { // 析构前释放桶数组及非空词条
	for (int i = 0; i < M; i++) // 逐一检查各桶
		if (ht[i]) delete ht[i]; // 释放非空的桶
	delete[] ht; // 释放桶数组
	delete lazyRemoval; // 释放懒惰删除标记
}



_DSA_END
#endif // !__HASHTABLE_H__
