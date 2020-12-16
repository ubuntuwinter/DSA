// string.h
#pragma once
#ifndef __STRING_H__
#define __STRINT_H__
#include "dsa.h"
#include <cstring>
#include <climits>
_DSA_BEGIN
/****************************************************************************
* Text		:   0	1	2	.	.	.	i-j	.	.	.	.	i	.	.	n-1
*               ------------------------|-------------------|--------------
* Pattern	:							0	.	.	.	.	j	.	.
*										|-------------------|
*****************************************************************************/
int match_BruteForce1(char* P, char* T) { // ��ƥ���㷨��Brute-force-1��
	size_t n = strlen(T), i = 0; // �ı������ȡ���ǰ���ܱȶ��ַ���λ��
	size_t m = strlen(P), j = 0; // ģʽ�����ȡ���ǰ���ܱȶ��ַ���λ��
	while (j < m && i < n) { // ������������ȶ��ַ�
		if (T[i] == P[j]) { // ��ƥ��
			i++; j++; // ��ת����һ�ַ�
		}
		else { // ����
			i -= j - 1; j = 0; // �ı������ˡ�ģʽ����λ
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
int match_BruteForce2(char* P, char* T) { // ��ƥ���㷨��Brute-force-2��
	size_t n = strlen(T), i = 0; // �ı������ȡ���ģʽ�����ַ��Ķ���λ��
	size_t m = strlen(P), j; // ģʽ�����ȡ���ǰ���ܱȶ��ַ���λ��
	for (i = 0; i < n - m + 1; i++) { // �ı����ӵ�i���ַ�����
		for (j = 0; j < m; j++) { // ģʽ���ж�Ӧ���ַ�����ȶ�
			if (T[i + j] != P[j]) break; // ��ʧ�䣬ģʽ����������һ���ַ�������һ�ֱȶ�
		}
		if (j >= m) break; // �ҵ�ƥ���Ӵ�
	}
	return i;
}

int* buildNext(char* P) { // ����ģʽ��P��next��
	size_t m = strlen(P), j = 0; // ��������ָ��
	int* N = new int[m]; // next��
	int t = N[0] = -1; // ģʽ��ָ��
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

int match_KMP(char* P, char* T) { // KMP�㷨
	int* next = buildNext(P); // ����next��
	int n = (int)strlen(T), i = 0; // �ı���ָ��
	int m = (int)strlen(P), j = 0; // ģʽ��ָ��
	while (j < m && i < n) { // ������������ȶ��ַ�
		if (0 > j || T[i] == P[j]) { // ��ƥ�䣬��P���Ƴ�����ࣨ�����жϵĴ��򲻿ɽ�����
			i++; j++; // ��ת����һ�ַ�
		}
		else { // ����
			j = next[j]; // ģʽ�����ƣ�ע�⣺�ı������û��ˣ�
		}
	}
	delete[] next; // �ͷ�next��
	return i - j;
}

/****************************************************************************
* 0						bc['X']							m-1
* |						|								|
* ......................X********************************
*						.|<----------'X' free---------->|
*****************************************************************************/
int* buildBC(char* P) { // ����Bad Charactor Shift��O(m+256)
	int* bc = new int[256]; // BC�����ַ���ȳ�
	for (size_t j = 0; j < 256; j++) bc[j] = -1; // ��ʼ�������ȼ��������ַ���δ��P�г���
	for (size_t m = strlen(P), j = 0; j < m; j++) // ��������ɨ��ģʽ��P
		bc[P[j]] = j; // ���ַ�P[j]��BC�����Ϊj���������������������㷨
	return bc;
}

int* buildSS(char* P) { // �������ƥ���׺���ȱ�O(m)
	int m = strlen(P); int* ss = new int[m]; // Suffix Size��
	ss[m - 1] = m; // �����һ���ַ����ԣ���֮ƥ�������׺��������P��
	// ���£��ӵ����ڶ����ַ�����������ɨ��P�����μ����ss[]�������
	for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--) {
		if ((lo < j) && (ss[m - hi + j - 1] <= j - lo)) // ���һ
			ss[j] = ss[m - hi + j - 1]; // ֱ�����ô�ǰ�Ѽ������ss[]
		else { // �����
			hi = j; lo = min(lo, hi);
			while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))
				lo--; // ����Աȴ���(lo, hi]ǰ�˵��ַ�
			ss[j] = hi - lo;
		}
	}
	return ss;
}

int* buildGS(char* P) { // ����ú�׺λ������O(m)
	int* ss = buildSS(P); // Suffix Size table
	size_t m = strlen(P); int* gs = new int[m]; // Good Suffix shift table
	for (size_t j = 0; j < m; j++) gs[j] = m; // ��ʼ��
	for (size_t i = 0, j = m - 1; j < UINT_MAX; j--) { // ������һɨ����ַ�P[j]
		if (j + 1 == ss[j]) // ��P[0, j] = P[m - j - 1, m)����
			while (i < m - j - 1) // ����P[m - j - 1]����ÿ���ַ�P[i]����
				gs[i++] = m - j - 1; // m - j - 1����gs[i]��һ��ѡ��
	}
	for (size_t j = 0; j < m - 1; j++) // �����㷨������ɨ��P[]���ַ���gs[j]���ϵݼ���ֱ����С
		gs[m - ss[j] - 1] = m - j - 1; // m - j - 1����gs[m - ss[j] - 1]ֵ��һ��ѡ��
	delete[] ss; return gs;
}

int match_BM(char* P, char* T) { // Boyer-Morre�㷨����ȫ�棬���Bad Character��Good Suffix��
	int* bc = buildBC(P); int* gs = buildGS(P); // ����BC����GS��
	size_t i = 0; // ģʽ��������ı�������ʼλ�ã���ʼʱ���ı�������룩
	size_t lengthT = strlen(T); // �ı����ĳ���
	size_t lengthP = strlen(P); // ģʽ���ĳ���
	while (lengthT >= i + lengthP) { // �������ƣ�������ܲ�ֹһ���ַ���ģʽ��
		int j = lengthP - 1; // ��ģʽ����ĩβ���ַ���ʼ
		while (P[j] == T[i + j]) // ��������ȶ�
			if (0 > --j) break;
		if (0 > j) // ������ƥ���׺ == ����ģʽ����˵���Ѿ���ȫƥ�䣩
			break; // ����ƥ��λ��
		else // �����ʵ����ƶ�ģʽ��
			i += max(gs[j], j - bc[T[i + j]]); // λ��������BC���GS��ѡ�����
	}
	delete[] gs; delete[] bc; // ����GS���BC��
	return i;
}

_DSA_END
#endif // !__STRING_H__
