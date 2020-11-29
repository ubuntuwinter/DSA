// stack_function.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
void convert(dsa::Stack<char>& S, __int64 n, int base) { // ʮ����������n��base���Ƶ�ת��
	static char digit[] // 0 < n, 1 < base <= 16, �½����µ���λ���ţ�����baseȡֵ��Χ�ʵ�����
		= { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0) { // �ɵ͵��ߣ���һ������½����µĸ���λ
		int remainder = (int)(n % base); S.push(digit[remainder]); // ��������ǰλ����ջ
		n /= base; // n����Ϊ���base�ĳ���
	}
} // �½������ɸߵ��͵ĸ���λ���Զ����±�����ջS��

bool paren(const char exp[], int lo, int hi) { // ���ʽ����ƥ���飬�ɼ����������
	dsa::Stack<char> S; // ʹ��ջ��¼�ѷ��ֵ���δƥ���������
	for (int i = lo; i <= hi; i++) { /* ��һ��鵱ǰ�ַ� */
		switch (exp[i]) {
		case '(':case '[':case '{':S.push(exp[i]); break;
		case ')':if ((S.empty()) || ('(' != S.pop())) return false; break;
		case ']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case '}':if ((S.empty()) || ('{' != S.pop())) return false; break;
		default: break; // �������ַ�һ�ɺ���
		}
	}
	return S.empty(); // �������ʽɨ�����ջ�����Բ����������ţ���ƥ�䣻����ջ�գ�ƥ��

}
_DSA_END