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
_DSA_END
#endif // !__STRING_H__