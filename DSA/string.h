// string.h
#pragma once
#ifndef __STRING_H__
#define __STRINT_H__
#include "dsa.h"
#include <cstring>
_DSA_BEGIN
/****************************************************************************
* Text		:   0	1	2	.	.	.	i-j	.	.	.	.	i	.	.	n-1
*               ------------------------|-------------------|--------------
* Pattern	:							0	.	.	.	.	j	.	.
*										|-------------------|
*****************************************************************************/
int match_BruteForce1(char* P, char* T) { // 串匹配算法（Brute-force-1）
	size_t n = strlen(T), i = 0; // 文本串长度、当前接受比对字符的位置
	size_t m = strlen(P), j = 0; // 模式串长度、当前接受比对字符的位置
	while (j < m && i < n) { // 自左向右逐个比对字符
		if (T[i] == P[j]) { // 若匹配
			i++; j++; // 则转到下一字符
		}
		else { // 否则
			i -= j - 1; j = 0; // 文本串回退、模式串复位
		}
	}
	return i - j;
}

/****************************************************************************
* Text		:   0	1	2	.	.	.	i	i+1	.	.	.	i+j	.	.	n-1
*               ------------------------|-------------------|--------------
* Pattern	:							0	1	.	.	.	j	.	.
*										|-------------------|
*****************************************************************************/
int match_BruteForce2(char* P, char* T) { // 串匹配算法（Brute-force-2）
	size_t n = strlen(T), i = 0; // 文本串长度、与模式串首字符的对齐位置
	size_t m = strlen(P), j; // 模式串长度、当前接受比对字符的位置
	for (i = 0; i < n - m + 1; i++) { // 文本串从第i个字符起，与
		for (j = 0; j < m; j++) { // 模式串中对应的字符逐个比对
			if (T[i + j] != P[j]) break; // 若失配，模式串整体右移一个字符，再做一轮比对
		}
		if (j >= m) break; // 找到匹配子串
	}
	return i;
}

int* buildNext(char* P) { // 构造模式串P的next表
	size_t m = strlen(P), j = 0; // “主”串指针
	int* N = new int[m]; // next表
	int t = N[0] = -1; // 模式串指针
	while (j < m - 1) {
		if (0 > t || P[j] == P[t]) {
			j++; t++;
			// N[j] = t;
			N[j] = (P[j] != P[t] ? t : N[t]);
		}
		else {
			t = N[t];
		}
	}
	return N;
}

int match_KMP(char* P, char* T) { // KMP算法
	int* next = buildNext(P); // 构造next表
	int n = (int)strlen(T), i = 0; // 文本串指针
	int m = (int)strlen(P), j = 0; // 模式串指针
	while (j < m && i < n) { // 自左向右逐个比对字符
		if (0 > j || T[i] == P[j]) { // 若匹配，或P已移出最左侧（两个判断的次序不可交换）
			i++; j++; // 则转到下一字符
		}
		else { // 否则
			j = next[j]; // 模式串右移（注意：文本串不用回退）
		}
	}
	delete[] next; // 释放next表
	return i - j;
}

_DSA_END
#endif // !__STRING_H__
