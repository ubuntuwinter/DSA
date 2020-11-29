// RPN.cpp
#pragma warning(disable:4996)
#include "stack.h"
#include "stack_function.h"
#include <ctype.h>
#include <string.h>
#include <cstdio>
_DSA_BEGIN
#define N_OPTR 9 // ���������
namespace {
	typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
	// �ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

	const char pri[N_OPTR][N_OPTR] = { // ��������ȵȼ�[ջ��][��ǰ]
		/*|--------------------��ǰ�����---------------------*/
		/*            +   -   *   /   ^   !   (   )  \0     */
		/* --  + */  '>','>','<','<','<','<','<','>','>',
		/* |   - */  '>','>','<','<','<','<','<','>','>',
		/* ջ  * */  '>','>','>','>','<','<','<','>','>',
		/* ��  / */  '>','>','>','>','<','<','<','>','>',
		/* ��  ^ */  '>','>','>','>','>','<','<','>','>',
		/* ��  ! */  '>','>','>','>','>','>',' ','>','>',
		/* ��  ( */  '<','<','<','<','<','<','<','=',' ',
		/* |   ) */  ' ',' ',' ',' ',' ',' ',' ',' ',' ',
		/* -- \0 */  '<','<','<','<','<','<','<',' ','='
	};
}

void readNumber(const char*& p, dsa::Stack<float>& stk) { // ����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
	stk.push((float)(*p - '0')); // ��ǰ��λ��Ӧ����ֵ��ջ
	while (isdigit(*(++p))) { // ֻҪ�������н��ڵ����֣�����λ���������������
		stk.push(stk.pop() * 10 + (float)(*p - '0')); // ����ԭ��������׷������λ������ֵ������ջ
	}
	if ('.' != *p) return; // �˺��С���㣬����ζ�ŵ�ǰ�������������
	float fraction = 1; // ������ζ�Ż���С������
	while (isdigit(*(++p))) { // ��λ����
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); // С������
	}
}

void append(char*& rpn, float opnd) { // ������������RPNĩβ
	int n = strlen(rpn); // RPN��ǰ����(��'\0'��β������n + 1)
	char buf[64];
	if (opnd != (float)(int)opnd) {
		sprintf(buf, "%.2f\0", opnd); // �����ʽ����
	}
	else {
		sprintf(buf, "%d\0", (int)opnd); // ������ʽ
	}
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); // ��չ�ռ�
	strcat(rpn, buf); // RPN�ӳ�
}

void append(char*& rpn, char optr) { // �����������RPN��β
	int n = strlen(rpn); // RPN��ǰ����(��'\0'��β������n = 1)
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3)); // ��չ�ռ�
	sprintf(rpn + n, "%c", optr); rpn[n + 2] = '\0'; // ����ָ���������
}

Operator optr2rank(char op) { // �������ת������
	switch (op) {
	case '+': return ADD; // ��
	case '-': return SUB; // ��
	case '*': return MUL; // ��
	case '/': return DIV; // ��
	case '^': return POW; // �˷�
	case '!': return FAC; // �׳�
	case '(': return L_P; // ������
	case ')': return R_P; // ������
	case '\0': return EOE; // ��ʼ������ֹ��
	default: exit(-1); // δ֪�����
	}
}

float calcu(char op, float pOpnd) {
	int result = 1;
	for (int i = 2; i <= (int)pOpnd; i++) {
		result *= i;
	}
	return (float)result;
}

float calcu(char op, float pOpnd1, float pOpnd2) {
	switch (op) {
	case '+': return pOpnd1 + pOpnd2; // ��
	case '-': return pOpnd1 - pOpnd2; // ��
	case '*': return pOpnd1 * pOpnd2; // ��
	case '/': return pOpnd1 / pOpnd2; // ��
	case '^': return (float)pow(pOpnd1, pOpnd2); // �˷�
	default: exit(-1); // δ֪�����
	}
}

char orderBetween(char op1, char op2) { // �Ƚ����������֮������ȼ�
	return pri[optr2rank(op1)][optr2rank(op2)];
}


float evaluate(const char* S, char*& RPN) { // �ԣ����޳��հף��ı��ʽS��ֵ����ת��Ϊ�沨�����ʽRPN
	dsa::Stack<float> opnd; dsa::Stack<char> optr; // ������ջ�������ջ
	optr.push('\0'); // β�ڱ�'\0'Ҳ��Ϊͷ�ڱ���ջ
	while (!optr.empty()) { // �������ջ�ǿ�֮ǰ�����������ʽ���ַ�
		if (isdigit(*S)) { // ����ǰ�ַ�Ϊ����������
			readNumber(S, opnd); append(RPN, opnd.top()); // ��������������������RPNĩβ
		}
		else { // ����ǰ�ַ�Ϊ���������
			switch (orderBetween(optr.top(), *S)) { // ������ջ�������֮������ȼ��ߵͷֱ���
			case '<': // ջ�����ȼ�����ʱ
				optr.push(*S); S++; // �����Ƴ٣���ǰ�������ջ
				break;
			case '=': // ���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
				optr.pop(); S++; // �����Ų�������һ���ַ�
				break;
			case '>': {// ջ����������ȼ����ߵ�ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop(); append(RPN, op); // ջ���������ջ��������RPNĩβ
				if ('!' == op) { // ������һԪ�����
					float pOpnd = opnd.pop(); // ֻ��ȡ��һ������������
					opnd.push(calcu(op, pOpnd)); // ʵʩһԪ���㣬�����ջ
				}
				else { // ����������Ԫ�������
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); // ȡ����ǰ������
					opnd.push(calcu(op, pOpnd1, pOpnd2)); // ʵʩ��Ԫ���㣬�����ջ
				}
				break;
			}
			default:
				exit(-1); // ���﷨���󣬲�������ֱ���˳�
			} // switch
		}
	}// while
	return opnd.pop(); // �������������ļ�����
}
_DSA_END