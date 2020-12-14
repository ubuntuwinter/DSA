// bitmap.h
#pragma once
#ifndef __BITMAP_H__
#define __BITMAP_H__
#define _CRT_SECURE_NO_WARNINGS
#include "dsa.h"
#include <cstring>
#include <cstdio>
_DSA_BEGIN
class Bitmap { // 位图Bitmap类
private:
	char* M; int N; // 比特图所存放的空间M[]，容量为N*sizeof(char)*8比特
protected:
	void init(int n) { 
		N = (n + 7) / 8;
		M = new char[N](); 
		memset(M, 0, N); 
	}
public:
	Bitmap(int n = 8) { init(n); } // 按指定或默认规模创建比特图（为测试暂时选用较小的默认值）
	Bitmap(const char* file, int n) { // 按指定或默认规模，从指定文件中读取比特图
		init(n); FILE* fp = fopen(file, "r"); fread(M, sizeof(char), N, fp); fclose(fp);
	}
	~Bitmap() { delete[] M; M = NULL; } // 析构时释放比特图空间

	void set(int k) { expand(k); M[k >> 3] |= (0x80 >> (k & 0x07)); }
	void clear(int k) { expand(k); M[k >> 3] &= ~(0x80) >> (k & 0x07); }
	bool test(int k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }

	void dump(const char* file) { // 将位图整体导出至指定文件，以便对此后的新位图批量初始化
		FILE* fp = fopen(file, "w"); fwrite(M, sizeof(char), N, fp); fclose(fp);
	}
	char* bits2string(int n) { // 将前n位转换为字符串——
		expand(n - 1); // 此时可能被访问的最高位为bitmap[n - 1]
		char* s = new char[n + 1]; s[n] = '\0'; // 字符串所占空间，由上层调用者负责释放
		for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
		return s; // 返回字符串位置
	}
	void expand(int k) { // 若被访问的Bitmap[k]已出界，则需扩容
		if (k < 8 * N) return; // 仍在界内，无需扩容
		int oldN = N; char* oldM = M;
		init(2 * k); // 与向量类似，加倍策略
		memcpy_s(M, N, oldM, oldN); delete[] oldM; // 原数据转移至新空间
	}
};
_DSA_END
#endif // !__BITMAP_H__
