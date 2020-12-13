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
	bool put(K k, V v) override; // 插入（禁止雷同词条，故可能失败）
	V* get(K k) override; // 读取 
	bool remove(K k) override; // 删除
};

static size_t hashCode(char c) { return (size_t)c; } // 字符
static size_t hashCode(int k) { return (size_t)k; } // 整数以及长长整数
static size_t hashCode(long long i) { return (size_t)((i >> 32) + (int)i); }
static size_t hashCode(char s[]) { // 生成字符串的循环移位散列码（cyclic shift hash code）
	int h = 0; // 散列码
	for (size_t n = strlen(s), i = 0; i < n; i++) { // 自左向右，逐一处理每一字符
		h = (h << 5) | (h >> 27); h += (int)s[i]; // 散列码循环左移5位，再累加当前字符
	}
	return (size_t)h; // 如此所得的散列码，实际上可理解位近似的“多项式散列码”
}

int primeNLT(int c, int n, const char* file) { // 根据file文件中的记录，在[c, n)内取最小的素数
	Bitmap B(file, n); // file已经按位图格式，记录了n以内的所有素数，因此只要
	while (c < n) { // 从c开始，逐位地
		if (B.test(c)) c++; // 测试即可
		else return c; // 返回首个发现的素数
	}
	return c; // 若没有这样的素数，返回n（实用中不能如此简化处理）
}

/**
* 沿关键码k对应的查找连，找到与之匹配的桶（供查找和删除词条时调用）
* 试探策略多种多样，可灵活选取；这里仅以线性试探策略为例
*/
template<typename K, typename V>
int Hashtable<K, V>::probe4Hit(const K& k) {
	int r = hashCode(k) % M; // 从起始桶（按除余法确定）出发
	while ((ht[r] && (k != ht[r]->key)) || (!ht[r] && lazilyRemoved(r))) {
		r = (r + 1) % M; // 沿查找链试探：跳过所有冲突的桶，以及带有懒惰删除标记的桶
	}
	return r; // 调用者根据ht[r]是否为空，即可判断查找是否成功
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

template<typename K, typename V>
bool Hashtable<K, V>::put(K k, V v) { // 散列表词条插入
	if (ht[probe4Hit(k)]) return false; // 雷同元素不必重复插入
	int r = probe4Free(k); // 为新词条找个空桶（只要装填因此控制得当，必然成功）
	ht[r] = new Entry<K, V>(k, v); ++N; // 插入（注意：懒惰删除标记无需复位）
	if (N * 2 > M) rehash(); // 装填因子高于50%后重散列
	return true; 
}

template<typename K, typename V>
V* Hashtable<K, V>::get(K k) { // 散列表词条查找算法
	int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : NULL; // 禁止词条的key值雷同
}

_DSA_END
#endif // !__HASHTABLE_H__
