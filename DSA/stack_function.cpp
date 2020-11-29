// stack_function.cpp
#include "stack.h"
#include "stack_function.h"
_DSA_BEGIN
void convert(dsa::Stack<char>& S, __int64 n, int base) { // 十进制正整数n到base进制的转换
	static char digit[] // 0 < n, 1 < base <= 16, 新进制下的数位符号，可视base取值范围适当扩充
		= { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0) { // 由低到高，逐一计算出新进制下的各数位
		int remainder = (int)(n % base); S.push(digit[remainder]); // 余数（当前位）入栈
		n /= base; // n更新为其对base的除商
	}
} // 新进制下由高到低的各数位，自顶而下保存于栈S中

bool paren(const char exp[], int lo, int hi) { // 表达式括号匹配检查，可兼顾三种括号
	dsa::Stack<char> S; // 使用栈记录已发现但尚未匹配的左括号
	for (int i = lo; i <= hi; i++) { /* 逐一检查当前字符 */
		switch (exp[i]) {
		case '(':case '[':case '{':S.push(exp[i]); break;
		case ')':if ((S.empty()) || ('(' != S.pop())) return false; break;
		case ']':if ((S.empty()) || ('[' != S.pop())) return false; break;
		case '}':if ((S.empty()) || ('{' != S.pop())) return false; break;
		default: break; // 非括号字符一律忽略
		}
	}
	return S.empty(); // 整个表达式扫描过后，栈中若仍残留（左）括号，则不匹配；否则（栈空）匹配

}
_DSA_END